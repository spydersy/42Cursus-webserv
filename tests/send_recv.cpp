#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <iostream>
#include <unistd.h>

#define PORT 8080



int main() {
    int     sockfd, new_sockfd, recv_length, sent_size, size_left = 0;
    struct  sockaddr_in address;
    struct  sockaddr_in conn_address;
    char    buffer[1024];

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd <= 0) {
        std::cerr << "Create Socket Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    // memset((char *)&address, 0, sizeof(address));
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
    
        socklen_t stor_size = sizeof(struct sockaddr_in);
        new_sockfd = accept(sockfd, (struct sockaddr *)&conn_address, &stor_size);
        if (new_sockfd == -1) {
            std::cerr << "Accepting Connection Failed!" << std::endl;
            exit(EXIT_FAILURE);
        }
        
        recv_length = recv(new_sockfd, &buffer, 1024, 0);
        std::cout << "Received:" << std::endl;
        while (recv_length == 1024) {
            std::cout << buffer;
            recv_length = recv(new_sockfd, &buffer, 1024, 0);
        }
        buffer[recv_length] = '\0';
        std::cout << buffer;
        std::cout << std::endl;
        std::string str_send = "HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 7\n\nHello!\n";
        sent_size = send(new_sockfd, str_send.c_str(), strlen(str_send.c_str()), 0);
        while (sent_size < strlen(str_send.c_str())) {
            size_left += sent_size;
            sent_size = send(new_sockfd, str_send.c_str() + size_left, strlen(str_send.c_str()), 0);
        }
        close(new_sockfd);
    }
    return (0);
}