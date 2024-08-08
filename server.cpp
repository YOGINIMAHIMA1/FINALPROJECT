#include <iostream>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>
#include <dirent.h>
#include "logger.h"

#define PORT 8080
#define BUFFER_SIZE 1024

void error(const char *msg) {
    perror(msg);
    exit(1);
}

void list_files(int client_fd) {
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_REG) {
                send(client_fd, dir->d_name, strlen(dir->d_name), 0);
                send(client_fd, "\n", 1, 0);
            }
        }
        closedir(d);
    }
}

void send_file(int client_fd, const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::string err_msg = "Error: File not found\n";
        send(client_fd, err_msg.c_str(), err_msg.length(), 0);
        return;
    }

    char buffer[BUFFER_SIZE] = {0};
    while (file.read(buffer, BUFFER_SIZE)) {
        send(client_fd, buffer, BUFFER_SIZE, 0);
    }
    send(client_fd, buffer, file.gcount(), 0);
    file.close();
}

void receive_file(int client_fd, const std::string &filename) {
    std::ofstream file(filename, std::ios::binary);
    char buffer[BUFFER_SIZE] = {0};
    int bytes_read;
    while ((bytes_read = read(client_fd, buffer, BUFFER_SIZE)) > 0) {
        file.write(buffer, bytes_read);
    }
    file.close();
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    Logger logger("server.log");

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        error("socket failed");
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        error("setsockopt");
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; // Bind to any address
    address.sin_port = htons(PORT);

    // Binding the socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        error("bind failed");
    }

    if (listen(server_fd, 3) < 0) {
        error("listen");
    }

    std::cout << "Server listening on port " << PORT << std::endl;

    while (true) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            error("accept");
        }

        read(new_socket, buffer, BUFFER_SIZE);
        std::string command(buffer);

        if (command == "LIST\n") {
            list_files(new_socket);
        } else if (command.substr(0, 8) == "DOWNLOAD") {
            std::string filename = command.substr(9);
            send_file(new_socket, filename);
            logger.log("File sent: " + filename);
        } else if (command.substr(0, 6) == "UPLOAD") {
            std::string filename = command.substr(7);
            receive_file(new_socket, filename);
            logger.log("File received: " + filename);
        }

        close(new_socket);
    }

    close(server_fd);
    return 0;
}
