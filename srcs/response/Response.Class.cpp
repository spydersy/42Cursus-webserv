/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:17:47 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/28 15:34:21 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** Constructors && Destructors : ***********************************************
*/
Response::Response( Request REQ, std::vector<Server> SERV ) :   _request(REQ),
                                                                _server(SERV),
                                                                _MT(_request, _server),
                                                                _responseBuffer(""),
                                                                _serverIndex(std::string::npos),
                                                                _isLocation(std::string::npos),
                                                                _root("") {
    std::cout << "Response Constructor Called :)" << std::endl;
}

Response::~Response(){
    std::cout << "Response Destructor Called :'( " << std::endl;
}

/*
** Getters && Setters :  
*/
Request             &Response::get_request( void ) { return this->_request; }
std::vector<Server> &Response::get_server( void ) { return this->_server; }
MimeTypes           &Response::get_MT( void ) { return this->_MT; }
std::string         &Response::get_responseBuffer( void ) { return this->_responseBuffer; }

/*
** METHODS : 
*/
void    Response::setHttpVersion( void ) {
    _responseBuffer.append("HTTP/1.1 ");
}

int     Response::getServerIndex() {
    this->_serverIndex = 0;
    return 0;
    /*
    for (std::vector<Server>::iterator it = this->_server.begin(); it != this->_server.end(); it++) {
        std::cout << "DBG MY_HOST : [" << it->get_host() << "] | RQST_HOST : [" << _request.getHost() << "]" << std::endl;
        if (it->get_host().compare(_request.getHost()) == 0) {
            this->_serverIndex = it - this->_server.begin();
            return it - this->_server.begin();
        }
    }
    return -1;
    */
}
void    Response::setHttpStatus( void ) {
    std::cout << "getServerIndex : " << getServerIndex() << std::endl;
    for (std::vector<Location>::iterator it = _server[_serverIndex].get_location().begin(); 
    it != _server[_serverIndex].get_location().end(); it++) {
        if (it->get_locations_path().compare(0, it->get_locations_path().length(), _request.getPath().substr(0, it->get_locations_path().length())) == 0) {
            if (_request.getPath().length() > it->get_locations_path().length()) {
                if (_request.getPath()[it->get_locations_path().length()] == '/') {
                    _isLocation = it - _server[_serverIndex].get_location().begin();
                    break ;
                }
                else
                    _isLocation = std::string::npos;
            }
            else {
                _isLocation = it - _server[_serverIndex].get_location().begin();
                break ;
            }
        }
    }
    _root = ((_isLocation == std::string::npos) ? _server[_serverIndex].get_root() : _server[_serverIndex].get_location()[_isLocation].get_root());
    std::cout << "LOCATION_DBG : " << _isLocation << std::endl;
    std::cout << "ROOT_DBG : [" << _root << "]" << std::endl;
    if (_isLocation != NPOS) {
        _request.getPath().erase(0, _server[_serverIndex].get_location()[_isLocation].get_locations_path().length());
    }
    std::cout << "REQ_DBG : [" << _request.getPath() << "] | LEN : " << _server[_serverIndex].get_location()[_isLocation].get_locations_path().length() << std::endl;
    // std::string filePath = _server.begin()->get_root();
    // filePath.append(_request.getPath());
    // std::ifstream   FILE;
    
    // std::cout << "FILE TO OPEN : " << filePath << std::endl;
    // FILE.open(filePath);
    // if (FILE.is_open()) {
    //     _responseBuffer.append("200 OK\nContent-Type: ");
    //     if (filePath.find(".html") != std::string::npos) {
    //         _responseBuffer.append("text/html\nContent-Length: ");
    //     }
    //     else {
    //         _responseBuffer.append("text/css\nContent-Length: ");
    //     }
    //     std::string FILEinLine;
    //     std::string buffer;
    //     int         len = 0;
    //     while (getline(FILE, buffer)) {
    //         FILEinLine.append(buffer).append("\n");
    //         len += buffer.length() + 1;
    //     }
    //     _responseBuffer.append(std::to_string(len)).append("\n\n").append(FILEinLine);
    // }
    // else {
    //     std::cerr << "Cant open FILE" << std::endl;
    //     _responseBuffer.append("404 OK\n");
    // }
}