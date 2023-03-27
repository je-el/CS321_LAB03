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
Code will be added into provided code from canvas. Below are th eriles to compile and run:  
- The Server must compile and run first before the Client files are compiled and run.   
[Server.c](Server.c) and [Client.c](Client.c) and [NewClient.c](NewClient.c) 

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

#### Improvements:
- In the future we will need to find a way to clean up the structure of sending and receiving the messsages. Right now the clients must send a message in order to receive any messages from the other client. 
	- one way we could do this is through using threading which can be seen to be attempted in [Our previous client file]([Notes_Progress/Client.c](https://github.com/je-el/CS321_LAB03/blob/main/Notes_progress/Client.c))
	- With threading we would use a thread to run the client function and another to make it so that the client is always listening for incoming messages. This way the user wont have to submit a message in order to receive messages through the server. 
- we would also like it if the server file can be updated to send updates to the console for example an output like this would be beneficial in knowing the status of each client:  
```
[timestamp] client 1 has sent a message to the server.
[timestamp] client 2 has received the message from client 1.
[timestamp] client 1 has disconnected.
[timestamp] client 2 has disconnected. There are no client files in the server now. Closing connection ...
```
