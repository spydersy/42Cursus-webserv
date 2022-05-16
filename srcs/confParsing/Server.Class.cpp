/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.Class.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:04:22 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/25 14:57:27 by abelarif         ###   ########.fr       */
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
                            _autoindex(""),
                            _whoAmI("Server"),
                            _redirections(std::vector<std::pair<std::string, std::string> >()),
                            _error_pages(std::vector<std::pair<std::string, std::string> >()),
                            _upload_path("") {}
Server::~Server(){}

Server      &Server::operator= ( const Server & src ) {
    this->_server_names = src._server_names;
    this->_host = src._host;
    this->_port = src._port;
    this->_root = src._root;
    this->_index = src._index;
    this->_methods = src._methods;
    this->_location = src._location;
    this->_CGI = src._CGI;
    this->_client_max_body_size = src._client_max_body_size;
    this->_autoindex = src._autoindex;
    this->_upload_path = src._upload_path;
    return *this;
}

/*
** GETTERS :
*/
std::vector<std::string>     &Server::get_server_names() { return this->_server_names; }
std::string                  &Server::get_host() { return this->_host; }
size_t                       &Server::get_port() { return this->_port; }
std::string                  &Server::get_root() { return this->_root; }
std::string                  &Server::get_client_max_body_size() { return this->_client_max_body_size; }
std::string                  &Server::get_autoindex() { return this->_autoindex; }
std::string                  &Server::get_upload_path() { return this->_upload_path; }
std::vector<std::string>     &Server::get_index() { return this->_index; }
std::vector<std::string>     &Server::get_methods() { return this->_methods; }
std::vector<Location>        &Server::get_location() { return this->_location; }
std::vector<CGI>             &Server::get_CGI() { return this->_CGI; }
SocketInfos					 &Server::get_socketInfos() { return this->_socketInfos; }
std::vector<std::pair<std::string, std::string> >   &Server::get_error_pages() { return this->_error_pages; }
std::vector<std::pair<std::string, std::string> >   &Server::get_redirections() { return this->_redirections; }

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
            this->_host = this->_host.substr(0, portIndex - 1);
            return true;
        }
        if (it == _host.end())
            return false;
    }
    return false;
}