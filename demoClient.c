//CS321_Lab03
//Group: Lisa Jacklin, Jewel Maldonado
//client file


// Client side C/C++ program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#define PORT 8080					//sets port number
   
int main(int argc, char const *argv[])
{
    int sock = 0, valread;				//variables required;
    
    struct sockaddr_in serv_addr;		//socket addressing 
    //sending first msg with a buffer for spacing
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    //checks to see if the socket was created with the file descriptor (socket())
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return -1;
    }
   
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
       
    //another set of fail safes, first for an incorrect address, next for issues with connection
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) 
    {
        printf("\nInvalid address/ Address not supported \n");
        return -1;
    }
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        printf("\nConnection Failed \n");
        return -1;
    }

    //when all failsafes are passed, a message between client and server can be sent.
    //sends the message to the server
    send(sock , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
	
    //reads the response from the socket or client
    valread = read( sock , buffer, 1024);
    printf("%s\n",buffer );
    return 0;
}

//outside of main, two functions, one for each client
void ClientOne() {
}

void ClientTwo() {
}
