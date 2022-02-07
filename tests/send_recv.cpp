#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <unistd.h>

#define PORT 8080

int main() {
    int     sockfd, new_sockfd, recv_length, sent_size, size_left = 0;
    struct  sockaddr_in address;
    struct  sockaddr_storage conn_address;
    char    buffer[1024];

    sockfd = sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0) {
        std::cerr << "Create Socket Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    memset((char *)&address, 0, sizeof(address));
    address.sin_family = AF_UNSPEC;
    address.sin_addr.s_addr = htonl(INADDR_ANY);
    address.sin_port = htons(PORT);
    
    if (bind(sockfd, (struct sockaddr *)&address, sizeof(address)) == -1) {
        std::cerr << "Bind Failed!" << std::endl;
        std::cerr << "Failure ERRNO: " << errno << std::endl;
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0) {
        std::cerr << "Listen Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    while (1) {
        std::cout << "Waiting for connection on port " << PORT << "..." << std::endl << std::endl;
    
        socklen_t stor_size = sizeof(struct sockaddr_storage);
        new_sockfd = accept(sockfd, (struct sockaddr *)&conn_address, &stor_size);
        if (new_sockfd == -1) {
            std::cerr << "Accepting Connection Failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        char *str_send = (char *)"HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 18\n\nHello From Server!\n";
        sent_size = send(new_sockfd, str_send, strlen(str_send), 0);
        // while (sent_size < strlen(str_send)) {
        //     size_left += sent_size;
        //     sent_size = send(new_sockfd, str_send + size_left, strlen(str_send), 0);
        // }
        
        recv_length = recv(new_sockfd, &buffer, 1024, 0);
        while (recv_length) {
            std::cout << "Received:" << std::endl << buffer << "Bytes: " << recv_length << std::endl;
            recv_length = recv(new_sockfd, &buffer, 1024, 0);
        }
        close(new_sockfd);
    }
    return (0);
}