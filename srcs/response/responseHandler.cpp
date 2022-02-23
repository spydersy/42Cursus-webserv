/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:35:59 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/23 21:49:05 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"
#include "../request/Request.hpp"
#include "../request/Utils.hpp"

#include <fcntl.h>

std::string root;

void    setHttpStatus(std::string &response, std::vector<Server> CONF, Request rqst)
{
    std::string filePath = CONF.begin()->get_root();
    filePath.append(rqst.getPath());
    std::ifstream   FILE;
    
    std::cout << "FILE TO OPEN : " << filePath << std::endl;
    FILE.open(filePath);
    if (FILE.is_open()) {
        response.append("200 OK\nContent-Type: ");
        if (filePath.find(".html") != std::string::npos) {
            response.append("text/html\nContent-Length: ");
        }
        else {
            response.append("text/css\nContent-Length: ");
        }
        std::string FILEinLine;
        std::string buffer;
        int         len = 0;
        while (getline(FILE, buffer)) {
            FILEinLine.append(buffer).append("\n");
            len += buffer.length() + 1;
        }
        response.append(std::to_string(len)).append("\n\n").append(FILEinLine);
    }
    else {
        std::cerr << KRED << "Cant open FILE" << KNRM << std::endl;
        response.append("404 OK\n");
    }
}

void    responseHandler(std::vector<Server> CONF, Request rqst, int socketFD)
{
    if (socketFD) {}
    std::cout << KGRN << "----------------------- RES_HANDLER -----------------------" << KNRM << std::endl;

    Response    response(rqst, CONF);
    
    response.setHttpVersion();
    response.setHttpStatus();
    
    std::cout << KGRN << "----------------------- RES_HANDLER : END -----------------------" << KNRM << std::endl;
}

    static char ngx_http_error_404_page[] =
    "<html> \r\n<head><title>404 Not Found</title></head> \r\n<body> \r\n<center><h1>404 Not Found</h1></center> \r\n";
