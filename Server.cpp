//CS321_Lab03
//Group: Lisa Jacklin, Jewel Maldonado
//Server file
//language: C++


// Server side C/C++ program to demonstrate Socket programming
// including necessary header files for socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

//define the port number as PORT 8080
#define PORT 8080

//main :)
int main(int argc, char const *argv[])
{
    //variables needed
    int server_fd, new_socket, valread;
    struct sockaddr_in address; // specifies a socket address 
    				// 
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    char *hello = "Hello from server";
       
    // Creating socket file descriptor using the socket() function
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
       
    // Forcefully attaching socket to the port 8080
    // set the socket options using setsocketopt() function to allow 
    // resue of the port number
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    //set up the server address structure by specifying
    //the address family
    address.sin_family = AF_INET;
    //IP Address
    address.sin_addr.s_addr = INADDR_ANY;
    //and the port number
    address.sin_port = htons( PORT );
       
    // Forcefully attaching socket to the port 8080
    //binding the socket to the address using bind()
    if (bind(server_fd, (struct sockaddr *)&address, 
                                 sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    //listen for incoming connections using listen()
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    //accept incoming connection using accept()
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
                       (socklen_t*)&addrlen))<0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    //read data from the socket using read() function and 
    //print it to the console
    valread = read( new_socket , buffer, 1024);
    printf("%s\n",buffer );
    // send a response to the client using send()
    //print message indication th emessage was sent
    send(new_socket , hello , strlen(hello) , 0 );
    printf("Hello message sent\n");
    return 0;
}
