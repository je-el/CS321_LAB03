# CS321_LAB03

### Group Members
- Lisa Jacklin
- Jewel Maldonado
  
## Lab 3  
### Assignment Task:
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
- [x] In the current version there is only one client. But you must create two different clients.  
- [x] Currently the messages are hardcoded in the program. But your code must read the client messages from the user.
- [x] Currently the server is accepting a client message (request) and sending a response message to the same client. In your new version, the server should forward the accepted message from one client to the other client.
- [x] The server should work properly only when two clients are up and connecting to it. If there is only one client connecting to the server then, the server will send a message complaining “only one client is up”
- [x] The process should not end only after one pass of message between server and client as it is now. Server will only stop if one of the clients sends ‘BYE’ message
- [x] The server process should be designed in such a way so that it cannot be aborted by hitting ctrl-c on that terminal
- [x] For the sake of simplicity, assume that both your client and servers are on the same machine i.e. localhost (127.0.0.1)
- [x] You may need to send the client process pids to the server to establish the connection

### Challenges and Obstacles:
- Making sure that both clients were connecting to the server
- knowing if the clients could be connected to the server through a single client file for both, or to create separate files for each client.
- getting the data recieved from one client to the server sent to the other client from the server (forwarding)
- making adjustments to send custom messages from client to client.
