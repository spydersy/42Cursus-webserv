#include "../include/webserv.hpp"
#include "SocketInfos.hpp"

int     create_servers( std::vector< Server > &servers ) {
    std::vector<int>    bound;
    for (std::vector<Server>::iterator it = servers.begin(); it != servers.end(); it++) {
        // Create Socket
        if ((*it).get_socketInfos().createSocket() == -1) {
            perror("Socket");
			return (-1);
        }

        // set Socket Address
        (*it).get_socketInfos().setSocketAddress((*it).get_port());

        if (find(bound.begin(), bound.end(), (*it).get_port()) != bound.end()) {
            // Bind Socket if not already bound
            if((*it).get_socketInfos().bindSocket() == -1) {
                perror("Bind");
                return (-1);
            }
        }

        // Listen on socket
        if ((*it).get_socketInfos().listenSocket() == -1) {
            perror("Listen");
			return (-1);
        }
    }
    return (0);
}