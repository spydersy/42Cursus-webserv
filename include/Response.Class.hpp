/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 15:17:13 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/23 17:08:21 by abelarif         ###   ########.fr       */
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
public:
    /*
    ** Constructors && Destructors :
    */
    Response( Request REQ, std::vector<Server> SERV ) : _request(REQ),
                                                        _server(SERV),
                                                        _MT(_request, _server),
                                                        _responseBuffer(""){
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

    void    setHttpStatus( void ) {
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
    }
};

#endif
