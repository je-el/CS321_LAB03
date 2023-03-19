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
x6. cannot be aborted by hitting control-c
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
    }
    else {
        printf("\n Connection Established.\n");
	  return;  
    }

    //within here, since connection has been established, a 
    //code block can be executed to print data.


     //one idea to communicate through messages from user
     char data[1024];
		int read = recv(clientSocket,data,1024,0);
		data[read] = '\0';
		printf("%s\n",data);

     char input[1024];
     scanf("%s", input);
     send (clientSocket, input, 1024, 0);
     
     read = recv(clientSocket,data,1024, 0);
     printf("%s\n", data);
     

    char msg[1024];
    while(1) {
        printf("%s: ", name);
        fgets(msg, 1024, stdin);
        send(sock , msg , strlen(msg) , 0 );
        if(strncmp(msg, "BYE", 3) == 0) {
            printf("Closing connection...\n");
            break;
        }
        valread = read(sock , buffer, 1024);
        printf("%s\n",buffer );
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
    //get_client_name(name, 1024);
    
    client(name);
    client(name2);

    //now to check that both of these clients have been created....?

    return 0;
}