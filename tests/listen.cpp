#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define PORT 80

int main() {
    int     sockfd;
    struct  sockaddr_in address;

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
        exit(EXIT_FAILURE);
    }

    if (listen(sockfd, 3) < 0) {
        std::cerr << "Listen Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening on port " << PORT << "..." << std::endl;
    return (0);
}