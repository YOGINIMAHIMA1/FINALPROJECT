   #                         `Documentation`
 `Overview`
*  `This project implements a basic network file-sharing application using C++      with TCP sockets. The server can list available files, send files to the client, and receive files from the client. The client can request a file list, download files, and upload files to the server. Basic logging is implemented on the server side to track file transfers.`


*         Aim - Network File Sharing Over Server and Client


#        Content
*       Introduction
*        SERVER CODE
*        CLIENT CODE
*       LOGGER UTILITY
*        ./server
*        ./client
*        Important Note
*       Server Code
*       Client Code
*       Contribute
*       Licence
*       Refrence
*       Team Members

      
       # Main  Refrence
  # Special Thanks To ShweatanK sir . This Project Has Been Made Under his Guidance.
      # We would like to express our sincere gratitude to Shweatank Sir for his invaluable guidance and support throughout the development of this project. Under his mentorship, we have gained profound knowledge and practical experience in several key areas:`

*  IPC (Inter-Process Communication): We have explored various IPC methods such as message queues, semaphores, and shared memory, learning how these techniques facilitate communication and synchronization between processes in complex systems.

*  POSIX Sockets: We delved into network communication using POSIX-compliant socket programming, mastering both connection-oriented (TCP) and connectionless (UDP) protocols, and understanding how to handle network data efficiently and securely.

Code Execution: We acquired insights into optimizing code execution, including techniques for improving performance, managing resources effectively, and understanding the intricacies of concurrent and parallel processing.

* Logger: We implemented sophisticated logging mechanisms to track application behavior, debug issues, and maintain comprehensive logs for audit and analysis, enhancing our ability to troubleshoot and improve software quality.

* Security: We learned best practices for securing communication channels and data, including encryption, authentication, and access control mechanisms, ensuring our applications adhere to high security standards.

* Testing: We came to appreciate the importance of rigorous testing strategies, including unit testing, integration testing, and stress testing, and learned how to design and execute tests that ensure software reliability and robustness.

* Bug Tracking- He help us in Bug Tacking and also tell us how to resolve these problems


#                                 Components

#            INTRODUCTION
`Network File Sharing- Network file sharing is a process that allows multiple users or devices within a network to access files and resources on a shared storage system. It enables collaboration and resource sharing, which is particularly useful in environments like businesses, schools, or any place where multiple users need access to the same files or resources.`

`Server (server.cpp)`

*       `Handles client connections, lists files, sends files to the client,   and  receives files from the client.`
*         Logs all file transfers using the Logger utility.
`Client (client.cpp)`

*     Connects to the server, requests file listings, downloads files, and  uploads files.
`Logger Utility (logger.h)`

*        A simple logging utility that logs messages to a file.
*         Used by the server to log file transfers.
    
  #          Compile the code:

*        Run g++ cmd This will compile both the server and client.
*          g++ -o output_name source_file.cpp

  #            Run the server:

*          Run ./server to start the server
`Run the client`

*         Run ./client to start the client.
#                
#                               Note
*   Make sure the client and server are on the same network or use the appropriate IP address when running them on different machines.
The server binds to INADDR_ANY, which allows it to accept connections from any IP address.
#                      logger 
*       The logger writes logs to server.log.

#            Server Code

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

void handleClient(int clientSocket, std::string clientIP) {
    char buffer[BUFFER_SIZE];
    int bytesRead;

    // Receive filename
    bytesRead = recv(clientSocket, buffer, BUFFER_SIZE, 0);
    if (bytesRead <= 0) {
        std::cerr << "[" << clientIP << "] Error receiving filename." << std::endl;
        close(clientSocket);
        return;
    }
    buffer[bytesRead] = '\0';
    std::string filename(buffer);  // Store the filename received from the client

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
#             Client Code
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
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Invalid address/Address not supported." << std::endl;
        return -1;
    }

    if (connect(socketFd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Connection error." << std::endl;
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

#  contribute
* We encourage everyone to collaborate on this project
* feel free to create issue if you find any Bug
* If you want to contribute please fork this repository.

# License
* License for the Network File Sharing Server & Client Project to FinalProject Members.

# References for the Network File Sharing Server & Client Project
    
`1. Standard Libraries & APIs:`
# C++ Standard Library Documentation
Description: The official reference for the C++ standard library functions and classes used in the project, such as <iostream>, <sys/socket.h>, and <netinet/in.h>.
`URL: https://en.cppreference.com/w/`
# POSIX Socket Programming
Description: Reference for POSIX-compliant socket programming, including the use of functions like socket(), bind(), listen(), and accept().
`URL: https://pubs.opengroup.org/onlinepubs/009695399/functions/xsh_chap02_02.html`
# 2. Logging Library:
`Custom Logger Implementation`
Description: Reference or inspiration for creating a simple logging system in C++ for tracking server and client activities.
URL: Logger Implementation Reference
 # 3. Encryption and Security:
`OpenSSL Documentation`
Description: Used for implementing SSL/TLS features in the project for secure communication between the server and client.
`URL: https://www.openssl.org/docs/`
# 4. Makefile Creation:
GNU Make Documentation
Description: Guide on writing and understanding Makefiles for automating the build process of the project.
`URL: https://www.gnu.org/software/make/manual/make.html`
 # 5. Tutorials & Examples:
Beej's Guide to Network Programming

Description: A well-known guide to network programming using sockets, covering both client and server code.
`URL: https://beej.us/guide/bgnet/`
# C++ Socket Programming Example
`Description: An example of simple client-server socket programming in C++, used as a reference for understanding basic concepts and implementation.`
`URL: https://www.geeksforgeeks.org/socket-programming-in-c-cpp/`
# 6. Development Environment:
# GCC Compiler Documentation
Description: Reference for using GCC to compile C++ programs, including specific flags and options relevant to the project.
`URL: https://gcc.gnu.org/onlinedocs/`
# Linux Man Pages
Description: Detailed documentation of system calls and functions used in the project, like close(), read(), and write().
`URL: https://man7.org/linux/man-pages/`

`Members`
* Mahima Bhardwaj
* Diksha Kumari
* Sunny


