/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positionHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:34:11 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/07 19:03:59 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

void    OUT_Position(std::string &FILE, std::string::iterator &it,
                    std::vector<Server> &vect, int *whereAmI)
{
    (void)vect;
    skipSpaces(FILE, it);
    if (it >= FILE.end()) {
        *whereAmI = EOF;
        return ;
    }
    if (FILE.compare(it - FILE.begin(), 6, KW_SERVER) == 0) {
        it+= 6;
        skipSpaces(FILE, it);
        if (FILE.compare(it - FILE.begin(), 1, "\n") == 0)
            it++;
        if (FILE.compare(it - FILE.begin(), 1, "{") == 0) {
            *whereAmI = POSITION_SERVER;
            Server  server;
            vect.push_back(server);
            it++;
        }
        else {
            errorStream("File : Syntax Error", true, 1);
        }
        nextChar(FILE, it);
        if (it >= FILE.end()) {
            *whereAmI = EOF;
            return ;
        }
        while (it < FILE.end()) {
            switch (validatedKeyword(FILE, it)) {
                case KW_SERVER_NAME_VALUE:
                    fill_server_name(FILE, it, vect, *whereAmI);
                    break ;
                default:
                    errorStream("ERRRRRRROOOOORORORORO", true, 1);
            }
        }
    }
}

void    SERVER_Position(std::string FILE, std::string::iterator &it, std::vector<Server> &vect, int *whereAmI)
{
    (void)whereAmI;
    (void)vect;
    std::cout << *it << std::endl;
    skipSpaces(FILE, it);
    std::cout << *it << std::endl;}

void    LOCATION_Position(std::string FILE, std::string::iterator &it, std::vector<Server> &vect, int *whereAmI)
{
    (void)whereAmI;
    (void)vect;
    std::cout << *it << std::endl;
    skipSpaces(FILE, it);
    std::cout << *it << std::endl;}

void    CGI_Position(std::string FILE, std::string::iterator &it, std::vector<Server> &vect, int *whereAmI)
{
    (void)whereAmI;
    (void)vect;
    std::cout << *it << std::endl;
    skipSpaces(FILE, it);
    std::cout << *it << std::endl;
}
