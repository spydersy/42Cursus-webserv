/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/13 09:03:23 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** RESPONSE_HANDLING : *********************************************************
*/
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

/*
** SERVER_SIDE : ***************************************************************
*/
void    server(std::vector<Server> CONF)
{
    int server_fd, new_socket; long valread;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    
    // Only this line has been changed. Everything is same.
    
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("In socket");
        exit(EXIT_FAILURE);
    }
    

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons( PORT );
    
    memset(address.sin_zero, '\0', sizeof address.sin_zero);
    
    
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("In bind");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 10) < 0)
    {
        perror("In listen");
        exit(EXIT_FAILURE);
    }
    while(1)
    {
        printf("\n+++++++ Waiting for new connection ++++++++\n\n");
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)
        {
            perror("In accept");
            exit(EXIT_FAILURE);
        }
        char buffer[30000] = {0};
        valread = read( new_socket , buffer, 30000);
        requestHandler(buffer, new_socket, CONF);
        printf("------------------ Connection : DONE -------------------");
        close(new_socket);
    }
}

/*
** PARSING : *******************************************************************
*/
std::vector<Server>     getData(std::string FILE)
{
    ServerData          data(POSITION_OUT);
    std::vector<Server> CONF;
    std::string::iterator   it = FILE.begin();

    OUT_Position(FILE, it, CONF, data);
    SERVER_Position(FILE, it, CONF, data);
    
    // printServer(CONF);
    server(CONF);
    return CONF;
}

std::vector<Server>     getServersData(std::ifstream &FILE)
{
    std::string                 LINE;
    std::string                 FILEINLINE;
    
    while (getline (FILE, LINE)) {
        if (!isEmptyLine(LINE))
            FILEINLINE += LINE + "\n";
    }
    return getData(FILEINLINE);
}

std::vector<Server>   readFile(std::string configFile)
{
    size_t          position;
    
    std::ifstream FILE;
    
    FILE.open(configFile.c_str());
    if (!FILE.is_open())
    {
        errorStream(configFile + " " + std::strerror(errno), true, 1);
    }
    position = configFile.find_last_of(".conf");
    if (position + 1 != configFile.length())
        errorStream(FORMAT_ERR, true, 1);
    return getServersData(FILE);
}

std::vector<Server>    confParsing(std::string configFILE)
{
    return (readFile(configFILE));
}
