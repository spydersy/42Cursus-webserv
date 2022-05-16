#ifndef UTILS_HPP
#define UTILS_HPP

#include "../include/webserv.hpp"
#include "Client.hpp"

/* ************************************************************************** */
/* Type Redifinition ******************************************************** */
/* ************************************************************************** */



typedef std::vector< std::pair< Client, Request > >		ClientRequest;
typedef std::vector< std::pair< Client, Response > >	ClientResponse;
typedef std::vector<Server>                             Servers;

#endif