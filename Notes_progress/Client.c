/*
CS 321 Lab 3
Edited and Coded by Jewel Maldonado and Lisa Jacklin
Client.c file
*/

//2nd  Client side C program to demonstrate Socket programming
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#define PORT 8080                                

//rather than the code creating the client being within main, 
//the code is within a function that will be implemented in main
void *client(void *arg)//char *name)
{
        char *name= (char *)arg;
        int valread;
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
                while(1){
                        printf("Client %d Enter Message: ", pid);
                        fgets(msg, 1024, stdin);
                        send(sock , msg , strlen(msg) , 0 ); // send message to server
                        /*if(strncmp(msg, "BYE", 3) == 0) {
                                printf("Closing connection...\n");
                                break;
                        } else {
                                valread = recv(sock, buffer, 1024, 0);
                                buffer[valread] = '\0';
                                printf("Client %d received: %s\n", pid, buffer);
                                valread = read(sock, buffer, 1024); // retrieves the message received from the other client
                                printf("%s\n",buffer); // will print the received message 
                        }*/
                }

        }

    close(sock);
}
// define the function that listens for incoming messages
void *receive_messages(void *arg) {
    int sock = *(int*)arg; // the socket file descriptor is passed as an argument
    char buffer[1024] = {0}; // create a buffer to store incoming messages
    int valread;// store the number of bytes read from the socket

        while(1) { // loop continuously to receive messages
                valread = recv(sock, buffer, 1024, 0);// read from the socket and store the number of bytes read in valread
                if (valread > 0) { // if bytes were read
                        buffer[valread] = '\0';// add a null terminator to the end of the message
                        printf("%s\n", buffer); // will print the received message
                        if(strncmp(buffer, "BYE", 3) == 0) {
                                printf("Closing connection...\n");
                                close(sock);
                                exit(0);
                        }
                }
        }
}

int main(int argc, char const *argv[])
{
        //these two were originally used to try and display the two separate clients 'names'
        //char name[1024];
        char name2[1024];
        //int sock = 0;
        pthread_t client_thread, recv_thread; // declare two threads
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        pthread_create(&client_thread, NULL, client, (void *)name);
        pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock);

        //pthread_create(&client_thread, NULL, client, (void *) name); // start client function in a separate thread
        //pthread_create(&recv_thread, NULL, receive_messages, (void *)&sock); // start receiving messages in a separate thread
        pthread_join(client_thread, NULL); // wait for client thread to finish
    

        return 0;
}
-- INSERT --

