#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>

#define MYPORT 7890

// bind to associate socket to a port in local machine

// bind the programm to the IP of the host i'ts running on

// int main()
// {
//     int sockfd;
//     struct addrinfo hints, *res;

//     memset(&hints, 0, sizeof(hints));
//     hints.ai_family = AF_UNSPEC;
//     hints.ai_socktype = SOCK_STREAM;
//     getaddrinfo("www.example.com", "http", &hints, &res);

//     sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    
//     bind(sockfd, res->ai_addr, res->ai_addrlen);
//     return (0);
// }


// bind a specific local IP address

int main()
{
    int sockfd;
    struct sockaddr_in my_addr;

    sockfd = socket(PF_INET, SOCK_STREAM, 0);

    
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(MYPORT);
    my_addr.sin_addr.s_addr = inet_addr("10.11.13.3");
    memset(my_addr.sin_zero, 0, sizeof(my_addr.sin_zero));
    
    bind(sockfd, (struct sockaddr *)&my_addr, sizeof(my_addr));
    return (0);
}