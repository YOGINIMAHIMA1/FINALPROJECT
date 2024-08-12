#                                Bug Tracker Report
                 `Project: Network File Sharing Server & Client`


#     1. Bug Details
#                                Bug ID: 001

`Title: Bind Error: Server Fails to Bind to Port`
*  Date: 2024-08-11
*  Status: Closed
*  Priority: High
*  Severity: Critical
*  Assigned to: To be assigned
#                                  Description
*  The server application occasionally fails to bind to the specified port, resulting in a "Bind error" message.  This issue prevents the server from starting and accepting connections, leading to downtime and unavailability of  the network file-sharing service.
                             `Steps to Reproduce`
*   Start the server application.
*   Observe the server output for a "Bind error" message.
                              `Expected Behavior`
*       The server should bind to the specified port and start listening for incoming connections without any errors.
`Actual Behavior`
*  The server sometimes fails to bind to the port, displaying a "Bind error" message and preventing the application from starting.
`3 Error Log`
# Example error message:
`Bind error.`
#                                  Fix Description
*  Port Availability Check: Implement a check to ensure the port is available before attempting to bind.
*  Retry Mechanism: Implement a retry mechanism that attempts to bind to the port multiple times before failing.
*   Error Logging: Improve error logging to provide more detailed information about the bind error, helping to   diagnose the issue more effectively.

#                                   Bug ID: 002
#       BUG- 1.Server Delayed Response
`Reported by: Mahima Bhardwaj, Diksha kumari ,Sunny`
* Date: [8-8-24]
* Status: Open
* Severity: High
* Priority: High
#                             Description:
*  The server sometimes takes an unexpectedly long time to respond after a file transfer is initiated by the client. This delay may affect the user experience, especially in real-time applications where quick acknowledgment is critical.

#                  Steps to Reproduce:
*    Start the server by running ./server.
*    Start the client by running ./client.
*    Send a file from the client to the server.
*    Observe the delay before the server acknowledges the file transfer completion. 
*    Observe the output in the client terminal.
#                  Expected Result:
*   The server should respond immediately after the file has been completely received.

#                 Actual Behaviour
*   The server delays its response by a few seconds, leading to potential performance issues.
#                 Root Cause Analysis
*   The cause of the delay is currently under investigation.   
#                 Solution Implemented:
*   Not yet implemented.   
#                      Testing:
*   No testing has been conducted as the issue is still open.
               

*   The client only displays "Available files:" with no files listed underneath.

#                   2. Bug Report: Server Not Exiting Properly
`Bug ID: 003`
* Date: [7-8-24]
* Status: Open
* Severity: High
* Priority: High
#                 Title: Server Not Exiting Properly
`Description:`

*      The server does not exit gracefully upon receiving termination signals or when it encounters an    errorThis *       issue can lead to resource leaks and potential instability in the system.


`Steps to Reproduce:`

*         Start the server application.
*      Attempt to terminate the server using a signal (e.g., Ctrl+C) or after a fatal error.
*        Observe that the server does not exit cleanly.
`Expected Behavior:`

*     The server should release all resources and exit gracefully upon receiving a termination signal or after      *   encountering a critical error.
`Actual Behavior:`

*   The server either hangs or leaves resources (like sockets) open, causing instability.
    Root Cause Analysis:

*   The issue appears to be related to improper handling of termination signals and resource cleanup.
`Solution Implemented:`

*  Not yet implemented.
#                               Testing:
* No testing has been conducted as the issue is still o

#       3. Bug Report: File Not Received at Server End Despite Successful Transfer
*       Reported by: Mahima Bhardwaj , Diksha Kumari, Sunny
*      Date: 2024-08-11
*      Status: Resolved
*       Priority: High
*      Severity: Major
 `Assigned to: Mahima Bhardwaj ,Diksha Kumari, Sunny`
*  Fixed by: To be assigned
  `Bug ID: 004`
`Title: File Not Received at Server End Despite Successful Transfer`

* Description:

*  The server does not correctly receive files, even though the client indicates that the file has been sent   successfully. This leads to missing files on the server side, causing disruptions in file availability and integrity.
# Steps to Reproduce:

*  Start the server application.
*  Connect a client to the server.
*  Send a file from the client to the server.
*  Observe the server to check if the file has been received.
#  Expected Behavior:

* The server should receive and store the file correctly after it has been sent from the client.
#  Actual Behavior:

* The client confirms the file has been sent, but the server does not receive or store the file as expected.
#  Root Cause Analysis:

 * Buffer size mismatch and improper handling of file transfer protocol may cause incomplete file transfer.
#  Solution Implemented:

* The server code has been modified to ensure proper file handling and dynamic buffer allocation. Additionally, the  contents of the file are now displayed on the server's terminal to verify successful reception.