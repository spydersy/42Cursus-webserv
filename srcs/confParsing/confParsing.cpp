/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/07 18:08:23 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"



std::vector<Server>     getData(std::string FILE)
{
    int                     whereAmI = POSITION_OUT;
    std::vector<Server> CONF;
    std::string::iterator   it = FILE.begin();

    while (it < FILE.end()) {
        if (whereAmI == POSITION_OUT) {
            OUT_Position(FILE, it, CONF, &whereAmI);
            std::cout << "whereAmI_DBG: " << whereAmI << std::endl;
        }
        else if (whereAmI == POSITION_SERVER) {
            // SERVER_Position(FILE, it, CONF, &whereAmI);
            
        }
        else if (whereAmI == POSITION_LOCATION) {
            // LOCATION_Position(FILE, it, CONF, &whereAmI);
            
        }
        else if (whereAmI == POSITION_CGI) {
            // CGI_Position(FILE, it, CONF, &whereAmI);
            
        }
    }
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
    std::cout << "DBG01: **************************" << std::endl;
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
    std::cout << "DBG00: **************************" << std::endl;
    return (readFile(configFILE));
}
