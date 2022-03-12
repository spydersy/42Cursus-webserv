/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/23 15:14:37 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

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
    // errorStream("END", true, 12);
    // server(CONF);
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
