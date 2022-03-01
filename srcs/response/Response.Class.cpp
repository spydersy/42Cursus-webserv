/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:17:47 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/01 02:36:35 by abelarif         ###   ########.fr       */
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
                                                                _serverIndex(NPOS),
                                                                _isLocation(NPOS),
                                                                _root(""),
                                                                _method("") {
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
size_t     Response::isLocation() {
    for (std::vector<Location>::iterator it = _server[_serverIndex].get_location().begin(); 
    it != _server[_serverIndex].get_location().end(); it++) {
        if (it->get_locations_path().compare(0, it->get_locations_path().length(), _request.getPath().substr(0, it->get_locations_path().length())) == 0) {
            if (_request.getPath().length() > it->get_locations_path().length()) {
                if (_request.getPath()[it->get_locations_path().length()] == '/') {
                    _isLocation = it - _server[_serverIndex].get_location().begin();
                    break ;
                }
                else
                    _isLocation = NPOS;
            }
            else {
                _isLocation = it - _server[_serverIndex].get_location().begin();
                break ;
            }
        }
    }
    return _isLocation;
}

template<typename T>
bool    Response::checkMethods( T &conf ) {
    std::vector<std::string>    methods = conf.get_methods();

    for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); it++) {
        std::cout << "DBG METHOD : RQST[" << _request.getMethod() << "] | conf[" << *it << "]" << std::endl;
        if ((*it).compare(_request.getMethod()) == 0) {
            _method = *it;
    std::cout << "TRUE ::::::::::::::::::::::::::::::::::::::::::" << std::endl;
            return true;
        }
    }
    std::cout << "FALSE ::::::::::::::::::::::::::::::::::::::::::" << std::endl;
    return false ; 
}

void    Response::setHttpStatus( void ) {
    std::cout << "11" << std::endl;
    getServerIndex();
    std::cout << "22" << std::endl;
    isLocation();
    std::cout << "33" << std::endl;
    _root = ((_isLocation == NPOS) ? _server[_serverIndex].get_root() : _server[_serverIndex].get_location()[_isLocation].get_root());
    std::cout << "44" << std::endl;
    if (_isLocation != NPOS)
        _request.getPath().erase(0, _server[_serverIndex].get_location()[_isLocation].get_locations_path().length());
    std::cout << "55" << std::endl;
    if (_isLocation != NPOS) {
        std::cout << "AA" << std::endl;
        checkMethods(_server[_serverIndex].get_location()[_isLocation]);
    }
    else {
        std::cout << "BB" << std::endl;
        checkMethods(_server[_serverIndex]);
    }
    std::cout << "66" << std::endl;
}

/*
    std::cout << " | LEN : " << _server[_serverIndex].get_location()[_isLocation].get_locations_path().length() << std::endl;
    std::string filePath = _server.begin()->get_root();
    filePath.append(_request.getPath());
    std::ifstream   FILE;
    
    std::cout << "FILE TO OPEN : " << filePath << std::endl;
    FILE.open(filePath);
    if (FILE.is_open()) {
        _responseBuffer.append("200 OK\nContent-Type: ");
        if (filePath.find(".html") != std::string::npos) {
            _responseBuffer.append("text/html\nContent-Length: ");
        }
        else {
            _responseBuffer.append("text/css\nContent-Length: ");
        }
        std::string FILEinLine;
        std::string buffer;
        int         len = 0;
        while (getline(FILE, buffer)) {
            FILEinLine.append(buffer).append("\n");
            len += buffer.length() + 1;
        }
        _responseBuffer.append(std::to_string(len)).append("\n\n").append(FILEinLine);
    }
    else {
        std::cerr << "Cant open FILE" << std::endl;
        _responseBuffer.append("404 OK\n");
    }
*/