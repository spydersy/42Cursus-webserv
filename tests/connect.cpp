#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define MYPORT 7890

int main()
{
    int sockfd;
    struct addrinfo hints, *res;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    getaddrinfo("www.example.com", "3490", &hints, &res);

    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == -1) {
        std::cerr << "Connect Failed!" << std::endl;
        exit(EXIT_FAILURE);
    }
    std::cerr << "Connected Successfully!" << std::endl;
    return (0);
}