#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8086;
const int BUFFER_SIZE = 1024;

void sendFile(int socket, const std::string& filePath) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file." << std::endl;
        return;
    }

    // Extract the filename from the file path
    std::string filename = filePath.substr(filePath.find_last_of("/\\") + 1);

    // Send the filename
    send(socket, filename.c_str(), filename.size(), 0);
    usleep(100); // Small delay to ensure filename is sent before FILE_START

    char buffer[BUFFER_SIZE];
    // Notify server about file transfer
    send(socket, "FILE_START", strlen("FILE_START"), 0);

    // Send file content
    while (file.read(buffer, BUFFER_SIZE)) {
        send(socket, buffer, file.gcount(), 0);
    }
    send(socket, buffer, file.gcount(), 0);  // Send remaining bytes

    // Notify server end of file transfer
    send(socket, "FILE_END", strlen("FILE_END"), 0);

    // Receive acknowledgment
    int bytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }

    std::cout << "File sent successfully." << std::endl;
}

void sendMessage(int socket, const std::string& message) {
    send(socket, message.c_str(), message.size(), 0);
    std::cout << "Message sent: " << message << std::endl;

    char buffer[BUFFER_SIZE];
    int bytesRead = recv(socket, buffer, BUFFER_SIZE, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        std::cout << "Server: " << buffer << std::endl;
    }
}

int main() {
    int socketFd;
    struct sockaddr_in serverAddr;
    std::string input;

    // Create socket
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        std::cerr << "Socket creation error." << std::endl;
        return -1;
    }

    // Connect to server
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) { // Use appropriate IP address
        std::cerr << "Invalid address/Address not supported." << std::endl;
        return -1;
    }

    if (connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection error." << std::endl;
        return -1;
    }

    // Authentication
    std::string username, password;
    std::cout << "Enter username: ";
    std::getline(std::cin, username);
    std::cout << "Enter password: ";
    std::getline(std::cin, password);

    // Send username and password
    send(socketFd, username.c_str(), username.size(), 0);
    usleep(100); // Small delay to ensure username is sent before password
    send(socketFd, password.c_str(), password.size(), 0);

    // Receive authentication response
    char buffer[BUFFER_SIZE];
    int bytesRead = recv(socketFd, buffer, BUFFER_SIZE, 0);
    if (bytesRead > 0) {
        buffer[bytesRead] = '\0';
        if (strcmp(buffer, "AUTH_OK") != 0) {
            std::cerr << "Authentication failed." << std::endl;
            close(socketFd);
            return -1;
        }
    } else {
        std::cerr << "Error receiving authentication response." << std::endl;
        close(socketFd);
        return -1;
    }

    // Loop for sending messages or files
    while (true) {
        std::cout << "Enter 'file' to send a file, 'message' to send a message, or 'exit' to quit: ";
        std::cin >> input;
        std::cin.ignore();  // Ignore the newline character after input

        if (input == "file") {
            std::string filePath;
            std::cout << "Enter file path: ";
            std::getline(std::cin, filePath);
            sendFile(socketFd, filePath);
        } else if (input == "message") {
            std::string message;
            std::cout << "Enter message: ";
            std::getline(std::cin, message);
            sendMessage(socketFd, message);
        } else if (input == "exit") {
            std::cout << "Exiting..." << std::endl;
            break;
        } else {
            std::cerr << "Invalid option." << std::endl;
        }
    }

    close(socketFd);
    return 0;
}
