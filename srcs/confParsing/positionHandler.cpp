/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positionHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:34:11 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/10 02:58:44 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

void    OUT_Position(std::string &FILE, std::string::iterator &it,
                    std::vector<Server> &vect, ServerData &data)
{
    (void)vect;
    skipSpaces(FILE, it);
    if (it >= FILE.end()) {
        data.whereAmI = EOF;
        return ;
    }
    if (FILE.compare(it - FILE.begin(), 6, KW_SERVER) == 0) {
        it+= 6;
        skipSpaces(FILE, it);
        if (FILE.compare(it - FILE.begin(), 1, "\n") == 0)
            it++;
        if (FILE.compare(it - FILE.begin(), 1, "{") == 0) {
            data.whereAmI = POSITION_SERVER;
            data.Bracket.first.push_back(true);
            data.Bracket.second.push_back(false);
            return ;
        }
        else
            errorStream(SYNTAX_ERR, true, 1);
    }
    else
        errorStream(SYNTAX_ERR, true, 1);
}

// void    LOCATION_Position(std::string &FILE, std::string::iterator &it,
//                     std::vector<Server> &vect, ServerData &data)
// {
    
// }

void    SERVER_Position(std::string &FILE, std::string::iterator &it,
                    std::vector<Server> &vect, ServerData &data)
{
    Server  server;

    vect.push_back(server);
    it++;
    nextChar(FILE, it);
    if (it >= FILE.end()) {
        data.whereAmI = EOF;
        return ;
    }
    while (it < FILE.end()) {
        switch (validatedKeyword(FILE, it)) {
            case KW_SERVER_NAME_VALUE:                                                  // server_name
                fill_server_name(FILE, it, vect, data);
                break ;
            case KW_LISTEN_VALUE:                                                       // listen
                fill_host_port(FILE, it, vect, data);
                break;
            case KW_CLOSED_BRACKET:                                                     // }
                setData(FILE, it, vect, data);
                break ;
            case KW_LOCATION_ROOT_VALUE:                                                // root
                fill_location_root(FILE, it, vect, data);
                break;
            case KW_ACCEPTED_METHOD_VALUE:
                fill_methods(FILE, it, vect, data);
                break;
            case KW_DEFAULT_FILE_VALUE:
                fill_index(FILE, it, vect, data);
                break;
            case KW_LOCATION_VALUE:
                // LOCATION_Position(FILE, it, vect, data);
                break;
            default:
                printServer(vect);
                errorStream("ERRRRRRROOOOORORORORO", true, 1);
        }
    }
}