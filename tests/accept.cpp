#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define PORT 80

int main() {
    int     sockfd, new_sockfd;
    struct  sockaddr_in address, conn_address;

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
    std::cout << "Waiting for connection on port " << PORT << "..." << std::endl;
    
    socklen_t sin_size = sizeof(struct sockaddr_in);
    new_sockfd = accept(sockfd, (struct sockaddr *)&conn_address, &sin_size);
    if (new_sockfd == -1) {
        std::cerr << "Accepting Connection Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Connected to port " << PORT << std::endl;
    std::cout << "Connected to port " << PORT << std::endl;
    std::cout << inet_ntoa(conn_address.sin_addr)<< " " << ntohs(conn_address.sin_port) << " ";
    return (0);
}