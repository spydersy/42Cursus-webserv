/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   requestHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/13 09:24:54 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/13 09:35:20 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

#include "Request.hpp"
#include "Utils.hpp"


void    requestHandler(std::vector<Server> CONF, std::string buffer, int socketFD)
{
    std::cout << KYEL << "----------------------- REQ_HANDLER -----------------------" << KNRM << std::endl;
    Request rqst;
    std::vector< std::string > parts;
    std::vector< std::string > headers;
    std::vector< std::string > body;
    parts = StringSplit(buffer, "\n");
    rqst.setMethod(parts[0]);
    // rqst.setPath(parts[0]);
    rqst.setVersion(parts[0]);
    std::cout << "Method: " << rqst.getMethod() << ", Host: " << rqst.getHost() << ", Port: " << rqst.getPort() << ", Path: " << rqst.getPath() << ", Version: " << rqst.getVersion() << std::endl;
    parts.erase(parts.begin());
    std::vector<std::string>::iterator it;
    for ( it = parts.begin(); it != parts.end(); it++) {
        if ((*it).find(":") != std::string::npos) {
            headers.push_back(*it);
            continue;
        }
        break ;
    }

    for (std::vector< std::string >::iterator it = headers.begin(); it != headers.end(); it++) {
		std::cout << *it << std::endl;
	}
    responseHandler(CONF, rqst, socketFD);
    std::cout << KYEL << "----------------------- REQ_HANDLER : END -----------------------" << KNRM << std::endl;
}