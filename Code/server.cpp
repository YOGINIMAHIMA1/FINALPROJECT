


#include <iostream>
#include <fstream>
#include <cstring>
#include <thread>
#include <vector>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8086;
const int BUFFER_SIZE = 1024;
const std::string USERNAME = "admin"; // Example username
const std::string PASSWORD = "password"; // Example password

void handleClient(int clientSocket, std::string clientIP) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Authenticate client
    std::string receivedUsername;
    std::string receivedPassword;

    // Receive username
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        std::cerr << "[" << clientIP << "] Error receiving username." << std::endl;
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';
    receivedUsername = buffer;

    // Receive password
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        std::cerr << "[" << clientIP << "] Error receiving password." << std::endl;
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';
    receivedPassword = buffer;

    // Check credentials
    if (receivedUsername != USERNAME || receivedPassword != PASSWORD) {
        std::cerr << "[" << clientIP << "] Authentication failed." << std::endl;
        close(clientSocket);
        return;
    }

    // Notify successful authentication
    send(clientSocket, "AUTH_OK", strlen("AUTH_OK"), 0);

    // Receive filename
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        std::cerr << "[" << clientIP << "] Error receiving filename." << std::endl;
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';
    std::string filename(buffer); // Store the filename received from the client

    // Log the filename and start receiving the file
    std::cout << "[" << clientIP << "] Receiving file (" << filename << ") from client..." << std::endl;

    while ((bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytesRead] = '\0';

        if (strcmp(buffer, "FILE_START") == 0) {
            std::ofstream outFile(filename, std::ios::binary);
            if (!outFile) {
                std::cerr << "Error opening file for writing." << std::endl;
                close(clientSocket);
                return;
            }
            std::cout << "[" << clientIP << "] Writing to file: " << filename << std::endl;
            while ((bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0)) > 0) {
                if (strcmp(buffer, "FILE_END") == 0) break;
                outFile.write(buffer, bytesRead);
            }
            outFile.close();
            std::cout << "[" << clientIP << "] File (" << filename << ") received successfully." << std::endl;
            send(clientSocket, "ACK: File received", strlen("ACK: File received"), 0);
        } else {
            std::cout << "[" << clientIP << "] Message from client: " << buffer << std::endl;
            send(clientSocket, "ACK: Message received", strlen("ACK: Message received"), 0);
        }
    }

    if (bytesRead < 0) {
        std::cerr << "[" << clientIP << "] Error receiving data." << std::endl;
    }

    close(clientSocket);
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrSize = sizeof(clientAddr);
    std::vector<std::thread> threads;

    // Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        std::cerr << "Socket creation error." << std::endl;
        return -1;
    }

    // Bind socket
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Bind error." << std::endl;
        return -1;
    }

    // Listen for connections
    if (listen(serverSocket, 5) < 0) {
        std::cerr << "Listen error." << std::endl;
        return -1;
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrSize);
        if (clientSocket < 0) {
            std::cerr << "Accept error." << std::endl;
            continue;
        }

        std::string clientIP = inet_ntoa(clientAddr.sin_addr);
        std::cout << "Client connected from IP: " << clientIP << std::endl;

        // Handle client in a new thread
        threads.emplace_back(handleClient, clientSocket, clientIP);
    }

    // Join threads (this will never actually happen in this example)
    for (auto& t : threads) {
        t.join();
    }

    close(serverSocket);
    return 0;
}
