#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "hacking.h"

#define PORT 7809		// The port users will be connecting to

int main(void)
{
	int						sockfd, new_sockfd;		// Listen on sock_fd, new connection on new_fd
	struct sockaddr_in		host_addr, client_addr;	//My address informaton
	socklen_t				sin_size;
	int						recv_length = 1, yes = 1;
	char					buffer[1024];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1)
		fatal("in socket()");
	if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		fatal("setting socket option SO_REUSEADDR");
	host_addr.sin_family = AF_INET;					// Host byte order
	host_addr.sin_port = htons(PORT);				// Short, network byte roder
	host_addr.sin_addr.s_addr = 0;					// Automatically fill with my IP
	memset(&(host_addr.sin_zero), '\0', 8);			// Zero the rest of the struct
	if (bind(sockfd, (struct sockaddr *)&host_addr, sizeof(struct sockaddr)) == -1)
		fatal("binding to socket");
	if (listen(sockfd, 5) == -1)
		fatal("listening on socket");
	while (1)
	{
		sin_size = sizeof(struct sockaddr_in);
		new_sockfd = accept(sockfd, (struct sockaddr *)&client_addr, &sin_size);
		if (new_sockfd == -1)
			fatal("accepting connection");
		printf("server: got connection from %s port %d\n",
				inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
		send(new_sockfd, "HTTP/1.1 200 OK\nServer: Test Server\nContent-Type: text/plain\nContent-Length: 13\n\nHello World!!\n", 96, 0);
		recv_length = recv(new_sockfd, &buffer, 1024, 0);
		while (recv_length)
		{
			printf("RECV: %d bytes\n", recv_length);
			dump((const unsigned char *)buffer, recv_length);
			recv_length = recv(new_sockfd, &buffer, 1024, 0);
		}
		close(new_sockfd);
	}
	return (0);
}
