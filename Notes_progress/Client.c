//CS321_Lab03
//Group: Lisa Jacklin, Jewel Maldonado
//client file

/*
Objective: 
1. create two different clients
2. read messages from the user input rather than them being hardcoded
3. the server should forward the accepted message from one client to the next
4.should only work properly when two clients are up
5.server should end when one client sends BYE.
6. cannot be aborted by hitting control-c
7.assume both client and server are one the same machine
8. send client pids to sever to establish connections
*/

// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080                                
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;                      //starting at socket zero
    struct sockaddr_in serv_addr;               //creating a structure for socket addresses in server address        

    char *hello = "Hello from client";
    char buffer[1024] = {0};
    //if the socket does not actually get created (thus equal 0 or less)
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
    //checks the connection between the socket and the server through server address.
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }
    else {
        //within here, data can be sent back and forth from client/server
        printf("\n Connection Established.\n");
    }

    send(sock , hello , strlen(hello) , 0 );      //think like signal sent, signal here being hello from the socket to the server

    printf("Hello message sent\n");
    valread = read( sock , buffer, 1024);         //reads the socket and space/buffer before the carriage return
    printf("%s\n",buffer );
    return 0;
}

//Client 1
void ClientOne() {

    /* one idea to communicate through messages from user
    * char data[1024];
		int read = recv(clientSocket,data,1024,0);
		data[read] = '\0';
		printf("%s\n",data);

    * char input[1024];
    * scanf("%s", input);
    * send (clientSocket, input, 1024, 0);
    * 
    * read = recv(clientSocket,data,1024, 0);
    * printf("%s\n", data);
     
    */
}

//Client 2
void ClientTwo() {

}
