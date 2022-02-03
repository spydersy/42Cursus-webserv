/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/03 21:22:18 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

std::vector<ServConfig>     getServersData(std::ifstream FILE)
{
    std::string buffer;
    
    while (getline (FILE, buffer)) {
        std::cout << buffer << std::endl;
    }
    return NULL;
}

std::vector<ServConfig>   readFile(std::string configFile)
{
    size_t          position;
    
    std::ifstream FILE(configFile);
    if (!FILE.is_open())
    {
        errorStream(configFile + " " + std::strerror(errno), true, 1);
    }
    position = configFile.find_last_of(".conf");
    if (position + 1 != configFile.length())
        errorStream(FORMAT_ERR, true, 1);
    return (getServersData(FILE));
}

std::vector<ServConfig>    confParsing(std::string configFILE)
{
    return (readFile(configFILE));
}