/*
CS 321 Lab 3
Edited and Coded by Jewel Maldonado and Lisa Jacklin
NewClient.c file

Objective: 
1. create two different clients
2. read messages from the user input rather than them being hardcoded
3. the server should forward the accepted message from one client to the next
4.should only work properly when two clients are up
5.server should end when one client sends BYE.
x6. cannot be aborted by hitting control-c in the sevrer, bbut I dunno if we also need it for the client file as well??
7.assume both client and server are one the same machine
8. send client pids to sever to establish connections

*/

// Client side C program to demonstrate Socket programming
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
	/*//this will also establish chatting between the clients too!
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
            printf("Client %d Chatting: ", pid);
            fgets(msg, 1024, stdin);
            send(sock , msg , strlen(msg) , 0 );
            if(strncmp(msg, "BYE", 3) == 0) {
                printf("Closing connection...\n");
                break;
            }
            valread = recv(sock, buffer, 1024, 0);
            buffer[valread] = '\0';
            printf("Client %d received: %s\n", pid, buffer);
        }
	//also see in main how the clients will show the different pid's of each client
	*/
	
	//this is another way to do it
	/*
	char pid_msg[1024];
	snprintf(pid_msg, sizeof(pid_msg), "PID:%d", pid);
	send(sock, pid_msg, strlen(pid_msg), 0);
	//recieve a message from the server
	int reading = recv(sock, buffer, 1024, 0);
        buffer[read] = '\0';
        printf("%s\n", buffer);
	//then you start chatting with the while loop
	*/

     	//one idea to communicate through messages from user
     	char data[1024];
		int byte_read = recv(sock,data,1024,0);
		data[byte_read] = '\0';
		printf("Client: %s\n",data);
    //within here, since connection has been established, a 
    //code block can be executed to print data.


     //one idea to communicate through messages from user
     char data[1024];
		int read = recv(sock,data,1024,0);
		data[read] = '\0';
		printf("Clcli1 %s\n",data);

     	char input[1024];
     		scanf("%s", input);
     		send (sock, input, 1024, 0);
     
     		byte_read = recv(sock,data,1024, 0);
     		printf("Client:%s\n", data);
     

    	char msg[1024];
    	while(1) {
        	printf("Client %d: %s",  client_num,name);
        	fgets(msg, 1024, stdin);
        	send(sock , msg , strlen(msg) , 0 );
        	if(strncmp(msg, "BYE", 3) == 0) {
            		printf("Closing connection...\n");
            		break;
        	}
    char msg[1024];
    while(1) {
        printf(":%s",name);
        fgets(msg, 1024, stdin);
        send(sock , msg , strlen(msg) , 0 );
        if(strncmp(msg, "BYE", 3) == 0) {
            printf("Closing connection...\n");
            break;
        }
        valread = byte_read;
        printf("%s\n",buffer );
    }

	  return;  
    }


    close(sock);
}

// get client name from user
//this is where issues begin, Edit this asap
/*since this chunk was giving issues, I have decided to pull it entirely out
void get_client_name(char *name, int size) {
    printf("Enter your name: ");
    fgets(name, size, stdin);
    name[strlen(name)-1] = '\0';
}
*/

int main(int argc, char const *argv[])
{
    char name[1024];
    char name2[1024];
    int cli1 = 1, cli2 = 2;
    //get_client_name(name, 1024);
    //lets use the pid's to show the names of each client rather than using client "1" client "2" idea.
    /*
    pid_t pid1 = getpid();
    client(pid1);
    pid_t pid2 = getpid();
    client(pid2);
    */
    client(name,cli1);
    client(name2,cli2);
    
    client(name);
    client(name2);

    return 0;
}
