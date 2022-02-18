/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   positionHandler.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:34:11 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/18 16:48:38 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

void    OUT_Position(std::string &FILE, std::string::iterator &it,
                    std::vector<Server> &vect, ServerData &data)
{
    Server server;
    std::cout << "OUT POS : ********************************************" << std::endl;
    if (data.whereAmI != POSITION_OUT) {
        errorStream(SYNTAX_ERR, true, 1);
    }
    static int firstTime = 1;
    if (firstTime == 1) {
        (void)vect;
        skipSpaces(FILE, it);
        if (it >= FILE.end()) {
            data.whereAmI = EOF;
            return ;
        }
        firstTime = 0;
    }
    std::cout <<  "DBG SERVER KW : [" << *(it + 0) << *(it + 1)<< *(it + 2)<< *(it + 3)<< *(it + 4)<< *(it + 5) << "]" << std::endl;
    if (FILE.compare(it - FILE.begin(), 6, KW_SERVER) == 0) {
        it+= 6;
        skipSpaces(FILE, it);
        if (it < FILE.end() && FILE.compare(it - FILE.begin(), 1, "\n") == 0)
            it++;
        if (FILE.compare(it - FILE.begin(), 1, "{") == 0) {
            data.whereAmI = POSITION_SERVER;
            data.Bracket.first.push_back(true);
            data.Bracket.second.push_back(false);
            it++;
            nextChar(FILE, it);
            skipSpaces(FILE, it);
            vect.push_back(server);
            return ;
        }
        else
            errorStream(SYNTAX_ERR, true, 10);
    }
    else
        errorStream(SYNTAX_ERR, true, 11);
}

void    LOCATION_Position(std::string &FILE, std::string::iterator &it,
                    std::vector<Server> &vect, ServerData &data)
{
    std::cout << KYEL << "[FILLED : LOCATION]" << KNRM << std::endl;
    Location    location;
    if (data.whereAmI != POSITION_SERVER)
        errorStream(SYNTAX_ERR, true, 12);

    std::string location_path;
    if (!(*it == ' ' || *it == '\t'))
        errorStream(KW_LOCATION, true, 1);
    skipSpaces(FILE, it);
    if (*it != '/')
        errorStream(KW_LOCATION, true, 1);
    location.get_locations_path() = getPath(FILE, it);
    skipSpaces(FILE, it);
    if (it < FILE.end() && *it == '\n')
        it++;
    skipSpaces(FILE, it);
    if (*it != '{')
        errorStream(SYNTAX_ERR, true, 13);
    it++;
    data.whereAmI = POSITION_LOCATION;
    nextChar(FILE, it);
    if (*it == '\n') {
        it++;
        nextChar(FILE, it);
    }
    vect.rbegin()->get_location().push_back(location);
    std::cout << "DONE"<< std::endl;
}

void    SERVER_Position(std::string &FILE, std::string::iterator &it,
                    std::vector<Server> &vect, ServerData &data)
{

    nextChar(FILE, it);
    if (it >= FILE.end()) {
        data.whereAmI = EOF;
        return ;
    }
    while (it < FILE.end()) {
        switch (validatedKeyword(FILE, it)) {
            case KW_SERVER_VALUE:                                                  // server_name
                OUT_Position(FILE, it, vect, data);
                break ;
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
                LOCATION_Position(FILE, it, vect, data);
                break;
            case KW_AUTOINDEX_VALUE:
                fill_autoindex(FILE, it, vect, data);
                break;
            case KW_CLIENT_BODY_SIZE_VALUE:
                fill_client_body_size(FILE, it, vect, data);
                break;
            default:
                errorStream("Unknown Keyword", true, 1);
        }
    }
}