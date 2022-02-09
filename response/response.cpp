/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 07:13:55 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/09 09:04:10 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include <fstream>

std::string FileInString(std::string path)
{
    std::ifstream   FILE;
    std::string     buffer;
    std::string     str;
    
    FILE.open(path);
    if (FILE.is_open()) {
        while (getline(FILE, buffer)) {
            str.append(buffer).append("\n");
        }
    }
    else {
        std::cerr << KRED << "ERROR FILE" << std::endl;
        exit (0);
    }
    return str;
}

void    responseHandler(Request rqst, int sock)
{
    std::cout << KGRN << "------------------ START: SESPONSE_HANDLER -------------------" << std::endl;

    std::string path = "./var/www/html/index.html";
    std::string response = "HTTP/1.1 200 OK\nContent-Type: text/html\nContent-Length: ";
    std::string str;
    
    str = FileInString(path);
    response.append(std::to_string(str.length())).append("\n\n").append(str);
    // response.append("\n\n");
    write(sock, response.c_str(), response.length());

    std::cout << "------------------   END: SESPONSE_HANDLER -------------------" << KNRM << std::endl;
}

int     main()
{
    server();
    return (0);
}