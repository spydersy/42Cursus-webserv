/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 07:13:55 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/09 10:19:05 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "response.hpp"
#include <fstream>
#include <sys/stat.h>
    

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

unsigned int binFileSize(std::string path)
{
    struct stat results;

    if (stat(path.c_str(), &results) == 0) {
        std::cout << "Binary file size is : " << results.st_size << std::endl;
        return results.st_size;
    }
    else {
        std::cerr << KRED << "Error reading binary File" << KNRM << std::endl;
        exit (100);
    }
    return results.st_size;
}

void    img_handler(Request rqst, int sock)
{
    std::string path = "./var/www/html/index.html";
    std::string response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg\nContent-Length: ";
    std::string str;
    std::ifstream FILE;

    int len = binFileSize(path);
    response.append(std::to_string(len)).append("\n\n");
    str = FileInString(path);
    
    FILE.open(path.c_str(), std::ios::in | std::ios::binary);

    response.append(str);
    // response.append("\n\n");
    write(sock, response.c_str(), len);

}

void    responseHandler(Request rqst, int sock)
{
    std::cout << KGRN << "------------------ START: SESPONSE_HANDLER -------------------" << std::endl;

    if (rqst.getPath().compare("/img_chania.jpg") == 0) {
        img_handler(rqst, sock);
    std::cout << "------------------   END: SESPONSE_HANDLER IMG -------------------" << KNRM << std::endl;
        return ;
    }
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