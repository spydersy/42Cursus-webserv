/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.Class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:04:22 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/01 02:45:40 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** CONSTRUCTOS & DESTRUCTORS : 
*/
Server::Server( void ) :    _server_names(std::vector<std::string>()),
                            _host(""),
                            _port(NPOS),
                            _root(""),
                            _index(std::vector<std::string>()),
                            _methods(std::vector<std::string>()),
                            _location(std::vector<Location>()),
                            _CGI(std::vector<CGI>()),
                            _whoAmI("Server") {}
Server::~Server(){}

/*
** GETTERS : 
*/
std::vector<std::string>     &Server::get_server_names() { return this->_server_names; }
std::string                  &Server::get_host() { return this->_host; }
size_t                       &Server::get_port() { return this->_port; }
std::string                  &Server::get_root() { return this->_root; }
std::string                  &Server::get_client_max_body_size() { return this->_client_max_body_size; }
std::vector<std::string>     &Server::get_index() { return this->_index; }
std::vector<std::string>     &Server::get_methods() { return this->_methods; }
std::vector<Location>        &Server::get_location() { return this->_location; }
std::vector<CGI>             &Server::get_CGI() { return this->_CGI; }

/*
** METHODS : 
*/
bool    Server::setHostPort() {
    
    
    for (std::string::iterator it = this->_host.begin(); it != this->_host.end(); it++) {
        if (*it == ':') {
            int     portIndex = it - this->_host.begin() + 1;
            while (++it != this->_host.end())
                if (!( '0' <= *it && *it <= '9'))
                    return (false);
            if (this->_host.begin() + portIndex == this->_host.end())
                return false;
            this->_port = std::stoi(this->_host.substr(portIndex));
            // this->_host = this->_host.substr(0, portIndex - 1);
            return true;
        }
        if (it == _host.end())
            return false;
    }
    return false;
}
void    Server::dbgServer()
{
    //  SERVER NAMES:
    {
        std::cout << "Server names: -------------------" << std::endl;
            for (std::vector<std::string>::iterator it = _server_names.begin(); it != _server_names.end(); it++)
                std::cout << "[" << *it << "] ";
            std::cout << std::endl;
    }
    //  HOST:
    {
        std::cout << "Host: ---------------------------" << std::endl;
            std::cout << "[" << _host << "] " << std::endl;
    }
    //  PORT:
    {
        std::cout << "Port: ---------------------------" << std::endl;
            std::cout << "[" << _port << "] " << std::endl;
    }
    //  ROOT:
    {
        std::cout << "Root: ---------------------------" << std::endl;
            std::cout << "[" << _root << "] " << std::endl;
    }
    //  CLIENT_MAX_BODY_SIZE:
    {
        std::cout << "Client_max_body_size: ---------------------------" << std::endl;
            std::cout << "[" << _client_max_body_size << "] " << std::endl;
    }
    //  INDEX:
    {
        std::cout << "Indexs: -------------------------" << std::endl;
            for (std::vector<std::string>::iterator it = _index.begin(); it != _index.end(); it++)
                std::cout << "[" << *it << "] ";
            std::cout << std::endl;
    }
    //  METHODS:
    {
        std::cout << "Methods: ------------------------" << std::endl;
            for (std::vector<std::string>::iterator it = _methods.begin(); it != _methods.end(); it++) {
                std::cout << "[" << *it << "] ";
            }
        std::cout << std::endl;
    }
    //  LOCATIONS:
    {
        std::cout << "Locations: ----------------------" << std::endl;
        for (std::vector<Location>::iterator it = _location.begin(); it != _location.end(); it++) {
            std::cout << "\tlocations: **********************" << std::endl;
            std::cout << "\tlocation_Path: [" << it->get_locations_path() << "]" << std::endl;
            std::cout << "\tautoindex: [" << it->get_autoindex() << "]" << std::endl;
            std::cout << "\tclient_max_body_size: [" << it->get_client_max_body_size() << "]" << std::endl;
            
            std::cout << "\tmethods: ";
            std::vector<std::string>::iterator methods_it = it->get_methods().begin();
            while (methods_it != it->get_methods().end()) {
                std::cout << "[" << *methods_it << "] ";
                methods_it++;
            }
            std::cout << std::endl;

            std::cout << "\tindexs: ";
            std::vector<std::string>::iterator index_it = it->get_index().begin();
            while (index_it != it->get_index().end()) {
                std::cout << "[" << *index_it << "] ";
                index_it++;
            }
            std::cout << std::endl;
        }
    }
}