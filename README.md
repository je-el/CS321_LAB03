# CS321_LAB03

### Group Members
- Lisa Jacklin
- Jewel Maldonado
  
## Lab 3  
#### Assignment Task
This assignment will familiarize 
you with the basic communication between two processes using system calls.
(work in group of two)  

### Objective:  
In this assignment you will create a single node, 
command line-based chat application to communicate between two client processes through a server process
The chat application will have two clients and one server
The clients will send and receive message to/from each other through the server.
You can start with the code shared in Canvas: **[Server.c](Server.c)** and **[Client.c](Client.c)**  

### Requirements:  
Modify the codes to do the following:  
1. In the current version there is only one client. But you must create two different clients.  
2. Currently the messages are hardcoded in the program. But your code must read the client messages from the user.
3. Currently the server is accepting a client message (request) and sending a response message to the same client. In your new version, the server should forward the accepted message from one client to the other client.
4. The server should work properly only when two clients are up and connecting to it. If there is only one client connecting to the server then, the server will send a message complaining “only one client is up”
5. The process should not end only after one pass of message between server and client as it is now. Server will only stop if one of the clients sends ‘BYE’ message
6. The server process should be designed in such a way so that it cannot be aborted by hitting ctrl-c on that terminal
7. For the sake of simplicity, assume that both your client and servers are on the same machine i.e. localhost (127.0.0.1)
8. You may need to send the client process pids to the server to establish the connection
