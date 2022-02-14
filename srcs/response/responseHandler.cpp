/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responseHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:35:59 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/14 05:08:13 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"
#include "../request/Request.hpp"
#include "../request/Utils.hpp"

std::string root;

void    setHttpVersion(std::string &response)
{
    response.append("HTTP/1.1 ");
}

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
    std::cout << KGRN << "----------------------- RES_HANDLER -----------------------" << KNRM << std::endl;

    // root = "/Users/abelarif/Desktop/42Cursus-webserv/root/errorsPages";
    MimeTypes   mm(rqst, CONF);
    
    if (mm.badExtension())
        std::cout << "BAD EX DBG" << std::endl;
    
    std::pair<std::string, std::string> mmtype = mm.get_mimetype();
    
    std::cout << "DBG FIRST : " << mmtype.first << " | DBG SECOND : " << mmtype.second << std::endl;
    std::string response;// = "HTTP/1.1 200 OK\nContent-Type: "; // text/plain\nContent-Length: 12\n\nHello world!";
    setHttpVersion(response);
    setHttpStatus(response, CONF, rqst);
    write(socketFD, response.c_str(), response.length());
    std::cout << KGRN << "----------------------- RES_HANDLER : END -----------------------" << KNRM << std::endl;
}