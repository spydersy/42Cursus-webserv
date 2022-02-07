#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>


#define PORT 7890


int main()
{
    int server_fd, new_socket;
    long valread;
    struct sockaddr_in address;
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        std::cerr << "Create Socket Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        std::cout << "Waiting for connection..." << std::endl;
        socklen_t   sin_size = sizeof(struct sockaddr_in);
        new_socket = accept(server_fd, (struct sockaddr *)&address, &sin_size);
        if (new_socket == -1)
        {
            std::cerr << "Accepting Socket Failed!" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        char buffer[1024] = {0};

        int valread = read(new_socket, buffer, 1024);
        std::cout << buffer;

        if (valread < 0) {
            std::cout << "No Bytes are there to read" << std::endl;
        }

        char *server_msg = (char *)"HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 12\n\nHello world!";
        write(new_socket, server_msg, strlen(server_msg));
        std::cout << "Closing Connection..." << std::endl;
        close(new_socket);
    }
    return (0);
}