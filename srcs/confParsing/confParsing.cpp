/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   confParsing.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/05 01:00:21 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

bool    isEMptyLine(std::string LINE)
{
    int i = -1;
    
    if (LINE.length() == 0)
        return true;
    while (LINE[++i])
    {
        if (LINE[i] == '\t')
            LINE[i] = ' ';
        if (LINE[i] != ' ' && LINE[i] != '\t')
            return false;
    }
    return true;
}
void     semicolonConditions(std::vector<std::string> content, std::string LINE)
{
    // server KEYWORD CONDITIONS:
    if (content[0].compare(KW_SERVER) == 0) {
        if (content.size() == 1)
            return ;
        else if (content.size() == 2 && content[0].compare("{") == 0)
            return ;
        else if (content.size() > 2
            || (content.size() == 2 && content[0].compare("{")))
            errorStream(" in LINE : " + LINE, true, 1);
    }
    // curly bracket CONDITIONS:
    if ((content[0].compare("{") == 0 || content[0].compare("}") == 0)
        && content.size() == 1)
        return ;
    else if (content[0].compare("{") == 0
        || content[0].compare("}") == 0)
        errorStream(" in LINE : " + LINE, true, 1);
    // other keywords:
    if (content[content.size() - 1].compare(";")) {
        errorStream(" in LINE : " + LINE, true, 1);
    }
}

void    semicolonChecker(std::string LINE)
{
    std::vector<std::string>    content;
    std::string                 buffer;

    std::istringstream f(LINE);
    while (getline(f, buffer, ' ')) {
        content.push_back(buffer);
    }
    semicolonConditions(content, LINE);
}

std::string    lineChecker(std::string LINE)
{
    if (isEmptyLine(LINE))
        return "";
    semicolonChecker(LINE);
}

std::vector<ServConfig>     getServersData(std::ifstream &FILE)
{
    std::string                 LINE;
    std::string                 FILEINLINE;
    std::vector<bool>           opened;
    std::vector<bool>           closed;
    std::vector<ServConfig>     Servers;
    
    while (getline (FILE, LINE)) {
        lineChecker(LINE);
        FILEINLINE += LINE;
    }
    std::cout << FILEINLINE << std::endl;
    return Servers;
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
    getServersData(FILE);
    std::cout << "*****************" << std::endl;
}

std::vector<ServConfig>    confParsing(std::string configFILE)
{
    return (readFile(configFILE));
}