   #                         `Documentation`
 `Overview`
*  `This project implements a basic network file-sharing application using C++      with TCP sockets. The server can list available files, send files to the client, and receive files from the client. The client can request a file list, download files, and upload files to the server. Basic logging is implemented on the server side to track file transfers.`


*         Aim - Network File Sharing Over Server and Client

#        Content
*       Introduction
*       LOGGER UTILITY
*        SERVER CODE
*        CLIENT CODE
*        MAKEFILE
*        make cmd for compilation
*        make run-server cmd
*        make run-client cmd
*        LIST
*        Important Note
*        logger
*        




#                                 Components

#            INTRODUCTION
`Network File Sharing- Network file sharing is a process that allows multiple users or devices within a network to access files and resources on a shared storage system. It enables collaboration and resource sharing, which is particularly useful in environments like businesses, schools, or any place where multiple users need access to the same files or resources.`

`Logger Utility (logger.h)`

*        A simple logging utility that logs messages to a file.
         Used by the server to log file transfers.
`Server (server.cpp)`

*       `Handles client connections, lists files, sends files to the client,   and  receives files from the client.`
*         Logs all file transfers using the Logger utility.
`Client (client.cpp)`

*     Connects to the server, requests file listings, downloads files, and  uploads files.
`Makefile`

*     Provides instructions for compiling and running the server and client programs.
*     Includes targets for building, cleaning, and running the programs.
    
  #          Compile the code:

*        Run make in the directory containing the code. This will compile both the server and client.
  #            Run the server:

*          Run make run-server to start the server.
`Run the client`

*        Run make run-client to start the client.
#                Client commands:

#          LIST: List the files available on the server.
*  DOWNLOAD <filename>: Download the specified file from the server.
*  UPLOAD <filename>: Upload the specified file to the server.
#                               Note
*   Make sure the client and server are on the same network or use the appropriate IP address when running them on different machines.
The server binds to INADDR_ANY, which allows it to accept connections from any IP address.
#                      logger 
*       The logger writes logs to server.log.



#  contribute
* We encourage everyone to collaborate on this project
* feel free to create issue if you find any Bug
* If you want to contribute please fork this repository.

# License
* License for the Network File Sharing Server & Client Project to FinalProject Members.

# References for the Network File Sharing Server & Client Project
`When documenting a project, it's essential to include references that provide credit to any external resources, libraries, or documentation that were consulted or used during the development process. Here’s a general list of references that you might include:`

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
# URL: https://gcc.gnu.org/onlinedocs/
# Linux Man Pages

Description: Detailed documentation of system calls and functions used in the project, like close(), read(), and write().
URL: https://man7.org/linux/man-pages/
7. Project Management:
# Bug Tracking and Reporting
* Description: Guidelines for creating a bug tracker report, including common practices for documenting issues in software development projects.
`URL: https://www.atlassian.com/software/jira/guides/use-cases/bug-tracking`
# 8. License Information:
`MIT License`
  * Description: The license under which this project is released, detailing the   permissions and limitations of using the software.
`URL: https://opensource.org/licenses/MIT`
9. Additional Resources:
`Stack Overflow Discussions`
* Description: General reference for troubleshooting, best practices, and community-driven answers to specific programming issues encountered during development.
`URL: https://stackoverflow.com/`
