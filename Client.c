/*
CS 321 Lab 3
Edited and Coded by Jewel Maldonado and Lisa Jacklin
Client.c file
*/

//2nd  Client side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080                                
   
//rather than the code creating the client being within main, 
//the code is within a function that will be implemented in main
void client(char *name)
{
	int sock = 0, valread;
	struct sockaddr_in serv_addr;              
	pid_t pid = getpid(); // getting the process ID of the client
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    	{
        	printf("\n Socket creation error \n");
        	return;
    	}
   
    	serv_addr.sin_family = AF_INET;
    	serv_addr.sin_port = htons(PORT);
       
    	if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    	{
    	    	printf("\nInvalid address/ Address not supported \n");
    	    	return;
    	}

    	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    	{
        	printf("\nConnection Failed \n");
        	return;
    	} else {
        	printf("\n Connection Established...\n");
   
    		//within here, since connection has been established, a 
    		//code block can be executed to print data.
	
		//send the PID to the server // adding this in so that we can send and recieve the PID to the server
		//one way to do this is:
		//this will also establish chatting between the clients too!
		char pid_str[1024];
        	sprintf(pid_str, "%d", pid); // convert pid to string

        	// send pid to server
        	send(sock, pid_str, strlen(pid_str), 0);
   
        	// receive welcome message from server
        	char welcome_msg[1024];
        	valread = recv(sock, welcome_msg, 1024, 0);
        	welcome_msg[valread] = '\0';
        	printf("%s\n", welcome_msg);
   
        	// chat loop
        	char msg[1024];
        	while(1) {
            		printf("Client %d Enter Message: ", pid);
            		fgets(msg, 1024, stdin);
            		send(sock , msg , strlen(msg) , 0 );//send message to server
            		valread = read(sock, buffer, 1024); // retrieves the message recieved from other client
			printf("%s\n",buffer); //will print the received message
			if(strncmp(msg, "BYE", 3) == 0) 
			{
                		printf("Closing connection...\n");
                		break;
            		} else { //added to make sure the recieved code is processed.
            			valread = recv(sock, buffer, 1024, 0);
            			buffer[valread] = '\0';
            			printf("Client %d received: %s\n", pid, buffer);
			} else 
        	}
	}

    close(sock);
}


int main(int argc, char const *argv[])
{
	//these two were originally used to try and display the two separate clients 'names'
	//char name[1024];
        char name2[1024];
    
    
    	//lets use the pid's to show the names of each client rather than using client "1" client "2" idea.
   	//pid_t pid2 = getpid();
    	client(name2);

    	return 0;
}
