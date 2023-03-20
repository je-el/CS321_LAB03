//CS321_Lab03
//Group: Lisa Jacklin, Jewel Maldonado
//Server file
//language: C


// Server side C program to demonstrate Socket programming
// including necessary header files for socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <stdbool.h>

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
        int max_clients = 30;
        int clients[max_clients];
        char client_names[max_clients][100];
        bool client_connected[max_clients];

        //initialize clients and client_connected arrays
        for (int i = 0; i < max_clients; i++) {
            clients[i] = 0;
            client_connected[i] = false;
        }

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
        while(1)
        { //while loop added
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,(socklen_t*)&addrlen))<0)
            {
                perror("accept");
                exit(EXIT_FAILURE);
            }
            //connecting clients
            for (int i = 0; i < max_clients; i++) {
                if (clients[i] == 0) {
                    clients[i] = new_socket;
                    printf("New client connected. Total clients: %d\\n", i+1);
                    char* welcome = "Hello and Welcome to the Chat Server!";
                    send(new_socket, welcome, strlen(welcome), 0);
                    client_connected[i] = true;
                    break;
                }
            }
            while(1){
            memset(buffer, 0, sizeof(buffer));
            valread = read(new_socket, buffer, 1024);
            if(valread ==0){
                //client has disconnected
                for (int i = 0; i < max_clients; i++) {
                    if (clients[i] == new_socket) {
                        printf("Client %s disconnected. Total Clients: %d\\n", client_names[i], i);
                        client_connected[i] = false;
                        clients[i] = 0;
                        break;
                    }
                }
                break;
            }
            // checking for command that changes client name
            if (buffer[0] == '/'){
                char* new_name = strtok(buffer + 1, " \\n");
                if (new_name != NULL) {
                    //extracting the name provided from user
                    for (int i = 0; i < max_clients; i++) {
                        if (clients[i] == new_socket) {
                            strncpy(client_names[i], new_name, 100);
                            printf("Client %d renamed to %s\\n", i, new_name);
                            break;
                        }
                    }
                }
            }else {

                //send message to all clients
                for (int i = 0; i < max_clients; i++) {
                    if (clients[i] != 0 && clients[i] != new_socket && client_connected[i]) {
                        char message[1124];
                        snprintf(message, 1124, "%s: %s", client_names[new_socket-4], buffer);
                        send(clients[i],    message, strlen(message), 0);
                    }
                }
            }

        }
    }
    return 0;
}

