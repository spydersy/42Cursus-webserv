/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/06 17:25:28 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

#define     OUT         0
#define     SERVER      1
#define     LOCATION    2
#define     CGI         3

std::vector<ServConfig>     getData(std::string FILE)
{
    int                     whereAmI = OUT;
    std::vector<ServConfig> CONF;
    std::string::iterator   it = FILE.begin();

    while (it < FILE.end()) {
        if (whereAmI == OUT) {
            OUT_Position(FILE, it, CONF, &whereAmI);
        }
        else if (whereAmI == SERVER) {
            // SERVER_Position(FILE, it, CONF, &whereAmI);
            
        }
        else if (whereAmI == LOCATION) {
            // LOCATION_Position(FILE, it, CONF, &whereAmI);
            
        }
        else if (whereAmI == CGI) {
            // CGI_Position(FILE, it, CONF, &whereAmI);
            
        }
    }
    return CONF;
}

std::vector<ServConfig>     getServersData(std::ifstream &FILE)
{
    std::string                 LINE;
    std::string                 FILEINLINE;
    
    while (getline (FILE, LINE)) {
        if (!isEmptyLine(LINE))
            FILEINLINE += LINE + "\n";
    }
    return getData(FILEINLINE);
}

std::vector<ServConfig>   readFile(std::string configFile)
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

std::vector<ServConfig>    confParsing(std::string configFILE)
{
    return (readFile(configFILE));
}