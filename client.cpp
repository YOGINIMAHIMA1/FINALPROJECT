#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <fstream>

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void list_files(int sock) {
    char buffer[BUFFER_SIZE] = {0};
    std::cout << "Available files:\n";
    while (read(sock, buffer, BUFFER_SIZE) > 0) {
        std::cout << buffer;
        memset(buffer, 0, BUFFER_SIZE);
    }
}

void download_file(int sock, const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    while ((bytes_read = read(sock, buffer, BUFFER_SIZE)) > 0) {
        file.write(buffer, bytes_read);
        memset(buffer, 0, BUFFER_SIZE);
    }
    file.close();
    std::cout << "File downloaded: " << filename << std::endl;
}

void upload_file(int sock, const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "File not found: " << filename << std::endl;
        return;
    }

    char buffer[BUFFER_SIZE] = {0};
    while (file.read(buffer, BUFFER_SIZE)) {
        send(sock, buffer, BUFFER_SIZE, 0);
    }
    send(sock, buffer, file.gcount(), 0);
    file.close();
    std::cout << "File uploaded: " << filename << std::endl;
}

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        error("Socket creation error");
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        error("Invalid address/Address not supported");
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Connection failed");
    }

    std::string command;
    std::cout << "Enter command (LIST, DOWNLOAD <filename>, UPLOAD <filename>): ";
    std::getline(std::cin, command);

    send(sock, command.c_str(), command.length(), 0);

    if (command == "LIST") {
        list_files(sock);
    } else if (command.substr(0, 8) == "DOWNLOAD") {
        std::string filename = command.substr(9);
        download_file(sock, filename);
    } else if (command.substr(0, 6) == "UPLOAD") {
        std::string filename = command.substr(7);
        upload_file(sock, filename);
    }

    close(sock);
    return 0;
}
