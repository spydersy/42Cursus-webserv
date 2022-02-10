#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <vector>

#define PORT 8000

struct server {
	int					sockfd;
	struct sockaddr_in	address;
	struct sockaddr_in	conn_address;
};

void	fill_servers(std::vector< server > &servers) {
	for (int i = 1; i < 11; i++) {
		server tmp;
		tmp.sockfd = socket(AF_INET, SOCK_STREAM, 0);
		if (tmp.sockfd <= 0) {
			servers.clear();
			std::cerr << "Create Socket Failed!" << std::endl;
        	exit(EXIT_FAILURE);
		}
		tmp.address.sin_family = AF_UNSPEC;
		tmp.address.sin_addr.s_addr = htonl(INADDR_ANY);
		tmp.address.sin_port = htons((i + 1) * PORT);
		if (listen(tmp.sockfd, 3) < 0) {
			std::cerr << "Listen Failed!" << std::endl;
			exit(EXIT_FAILURE);
		}
		servers.push_back(tmp);
	}
}

int main() {
	std::vector< server >	servers;
	fill_servers(servers);
	
    return (0);
}