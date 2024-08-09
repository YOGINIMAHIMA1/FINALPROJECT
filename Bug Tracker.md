#                                Bug Tracker Report
                 `Project: Network File Sharing Server & Client`
#                                   Bug ID: 001
#        Title: File list not displayed in client when LIST command is issued
`Reported by: Mahima Bhardwaj, Diksha kumari ,Sunny`
`Date: [8-8-24]`
`Status: Open`
`Severity: High`
`Priority: High`
#                             Description:
*  When the client issues the LIST command to the server, the client only displays * "Available files:" without listing any of the files present in the server's * directory. The expected behavior is for the client to display all available files in the server's directory.

#                  Steps to Reproduce:
*  Start the server by running ./server.
*   Start the client by running ./client.
*   In the client terminal, type LIST and press Enter.
*    Observe the output in the client terminal.
#                  Expected Result:
* The client should display a list of files available in the server's current working directory, formatted as follows:



#                Available files:
`file1.txt`
`file2.jpg`
`example.pdf`
`Actual Result:`
*   The client only displays "Available files:" with no files listed underneath.

#                       Possible Cause:
*    The issue may be due to:
*  Server-Side: The server might not be sending the list of files correctly, or it could be sending them in an incomplete or incorrect format.
Client-Side: The client might not be correctly receiving or displaying the file list. It could be failing to process multiple chunks of data if the list is too long for one buffer.

`Logs/Console Output:`
`Server Output:`

*   Server is listening on port 8080
# Client Output:
`Available files:`
*  Attachments:
*  server.cpp
*   client.cpp
*   logger.h
*   Makefile
#  Workaround:
*    No known workaround at this time.

#    Suggested Fix:
*  Step 1: Modify the server code to print file names to the console before sending them to the client. This will help verify that the server is correctly identifying and sending the files.

*  Step 2: Ensure that the client is correctly concatenating and displaying all chunks of data received from the server.

* Step 3: Test by running the server and client again, checking for correct output.

`Notes:`
* Ensure that the server sends a termination signal (END_OF_LIST) after sending the complete file list.
* Verify that the client properly interprets and handles the termination signal, * printing all received file names before the signal is received.
Comments:
* [Mahima Bhardwaj]: "This issue needs to be resolved urgently as it affects the core functionality of listing files on the server."
# Resolution:
`Status: Pending`

# Test Case:
Once fixed, the test case should involve starting both the server and client, issuing the LIST command from the client, and verifying that the client displays the list of files.

# Closing Remarks:
This bug is critical as it impacts the primary user interaction (file listing) between the client and server. It should be prioritized for resolution.

# Bug History:
Date	Action	Updated By	                   Comment
[7-8-24]	Reported	[Diksha]	            Initial report created
[7-8-24]	Assigned	[Sunny]	               Issue assigned for fixing
[7-8-24]	In Progress	 [Mahima]	           Working on a fix
[8-8-24]	In Progress	[Mahima]	         Fix applied and committed
[8-8-24]	Open	   [Mahima]	              Verified and closed


`Summary`
* This bug tracker report should help keep track of the issue and ensure it gets   resolved efficiently. So we Update it from time to time.