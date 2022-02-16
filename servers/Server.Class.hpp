/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.Class.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:22:45 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/08 03:15:51 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_CLASS_HPP
#define SERVER_CLASS_HPP

#include "Location.Class.hpp"
#include "CGI.Class.hpp"
#include <iostream>
#include <vector>

/*
** DEFAULT CONFIGFILE: *********************************************************
** No write permission: -r--r--r--  conf/default.conf
*/
# define DFLTCONF   "./conf/default.conf"

/*
** CONFIGFILE  KEYWORDS: *******************************************************
*/
# define KW_SERVER              "server"
# define KW_SERVER_NAME         "server_name"           //  Server_name
# define KW_ERR_PAGE            "error_page"            //  Default error pages
# define KW_LISTEN              "listen"                //  Listen HOST:PORT
# define KW_CLIENT_BODY_SIZE    "client_max_body_size"  //  Limit client body size
# define KW_ACCEPTED_METHOD     "allow_methods"         //  Define a list of accepeted HTTP Methods
# define KW_AUTOINDEX           "autoindex"             //  Turn on or off directory listing
# define KW_DEFAULT_FILE        "index"                 //  Default file to answer if the request is a directory
# define KW_LOCATION            "location"              //  Define a directory or a file from where the file should be search
# define KW_LOCATION_ROOT       "root"                  //  The KW_LOCATION is rooted to KW_LOCATION_ROOT

# define KW_CLOSED_BRACKET            9000
# define KW_SERVER_VALUE              9001          
# define KW_SERVER_NAME_VALUE         9002
# define KW_ERR_PAGE_VALUE            9003
# define KW_CLIENT_BODY_SIZE_VALUE    9004
# define KW_ACCEPTED_METHOD_VALUE     9005
# define KW_AUTOINDEX_VALUE           9006
# define KW_DEFAULT_FILE_VALUE        9007
# define KW_LOCATION_VALUE            9008
# define KW_LOCATION_ROOT_VALUE       9009
# define KW_LISTEN_VALUE              9010

class ServerData
{
public:
	int                                                 whereAmI;
	std::pair<std::vector<bool>, std::vector<bool> >    Bracket;    

	ServerData(int POSITION) : whereAmI(POSITION) {}
	~ServerData() {}
};

class Server
{
private:
	std::vector<std::string>     _server_names;
	std::string                  _host;
	int                          _port;
	std::string                  _root;
	std::vector<std::string>     _index;
	std::vector<int>             _methods;
	std::vector<Location>        _location;
	std::vector<CGI>             _CGI;
	
	// bool    validated_server_name(std::string name) {
	//     if (name) {
	//         // set coonditions to validate server_name ;
	//     }
	//     return true;
	// }
public:
	Server( void ) :    _server_names(std::vector<std::string>()),
						_host(""),
						_port(-1),
						_root(""),
						_index(std::vector<std::string>()),
						_methods(std::vector<int>()),
						_location(std::vector<Location>()),
						_CGI(std::vector<CGI>())
						{ std::cout << "Server Constructor Called :) " << std::endl; }
	~Server(){ std::cout << "Server Destructor Called :') " << std::endl;}


	//  GETTERS :
	std::vector<std::string>     &get_server_names() { return this->_server_names; }
	std::string                  &get_host() { return this->_host; }
	int                          &get_port() { return this->_port; }
	std::string                  &get_root() { return this->_root; }
	std::vector<std::string>     &get_index() { return this->_index; }
	std::vector<int>             &get_methods() { return this->_methods; }
	std::vector<Location>        &get_location() { return this->_location; }
	std::vector<CGI>             &get_CGI() { return this->_CGI; }





































































	void    dbgServer()
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
				for (std::vector<int>::iterator it = _methods.begin(); it != _methods.end(); it++) {
					
					std::cout << "[";
					if (*it == METH_DELETE) {
						std::cout << "DELETE";
					}
					else if (*it == METH_GET) {
						std::cout << "GET";
					}
					else if (*it == METH_POST) {
						std::cout << "POST";
					}
					else {
						std::cout << "UNKNOWN";
					}
					std::cout << "] ";
				}
				std::cout << std::endl;
		}
	}
};

#endif