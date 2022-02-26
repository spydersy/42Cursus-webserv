/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/26 18:03:08 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RSPONSE_CLASS_HPP
#define RSPONSE_CLASS_HPP

#include "./webserv.hpp"

class Response
{
private:
    Request             _request;
    std::vector<Server> _server;
    MimeTypes           _MT;
    std::string         _responseBuffer;
    size_t              _serverIndex;
    size_t              _isLocation;
    std::string         _root;
public:
    /*
    ** Constructors && Destructors :
    */
    Response( Request REQ, std::vector<Server> SERV ) : _request(REQ),
                                                        _server(SERV),
                                                        _MT(_request, _server),
                                                        _responseBuffer(""),
                                                        _serverIndex(std::string::npos),
                                                        _isLocation(std::string::npos),
                                                        _root("") {
        std::cout << "Response Constructor Called :)" << std::endl;
    }
    ~Response(){
        std::cout << "Response Destructor Called :'( " << std::endl;
    }
    /*
    ** Getters && Setters :  
    */
    Request             &get_request( void ) { return this->_request; }
    std::vector<Server> &get_server( void ) { return this->_server; }
    MimeTypes           &get_MT( void ) { return this->_MT; }
    std::string         &get_responseBuffer( void ) { return this->_responseBuffer; }
    /*
    ** METHODS : 
    */
    void    setHttpVersion( void ) {
        _responseBuffer.append("HTTP/1.1 ");
    }
    
    int     getServerIndex() {
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
    void    setHttpStatus( void ) {
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
};

#endif
