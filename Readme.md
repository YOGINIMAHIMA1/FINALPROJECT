   #                         `Documentation`
 `Overview`
*  `This project implements a basic network file-sharing application using C++      with TCP sockets. The server can list available files, send files to the client, and receive files from the client. The client can request a file list, download files, and upload files to the server. Basic logging is implemented on the server side to track file transfers.`

#                                 Components
`Logger Utility (logger.h)`

*        A simple logging utility that logs messages to a file.
         Used by the server to log file transfers.
`Server (server.cpp)`

*       `Handles client connections, lists files, sends files to the client,   and  receives files from the client.`
*         Logs all file transfers using the Logger utility.
`Client (client.cpp)`

*    Connects to the server, requests file listings, downloads files, and  uploads files.
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
`Summary`
*   Make sure the client and server are on the same network or use the appropriate IP address when running them on different machines.
The server binds to INADDR_ANY, which allows it to accept connections from any IP address.
#                      logger 
*       The logger writes logs to server.log.