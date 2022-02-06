/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:24 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/06 17:31:57 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "ServConf.Class.hpp"
#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include <string>
#include <stdlib.h>

/*
** COLORS DEFINITION: **********************************************************
*/
# define KNRM       "\x1B[0m"
# define KRED       "\x1B[31m"
# define KGRN       "\x1B[32m"
# define KYEL       "\x1B[33m"
# define KBLU       "\x1B[34m"
# define KMAG       "\x1B[35m"
# define KCYN       "\x1B[36m"
# define KWHT       "\x1B[37m"

/*
** ERRORS DESCRIPTION: *********************************************************
*/
# define ARGS_ERR       "\nUsage: ./webserv ./CONFIG/FILE/PATH"
# define FORMAT_ERR     "Format insupported"


/*
** DATA STRUCTRS: **************************************************************
*/



/*
** FUNCTIONS PROTOTYPES: *******************************************************
*/
int     webserv(int argc, char **argv);
/*
** SHARED FUNCTIONS:
*/
// first Argument : String variable That describe the error.
// second Argument: bool variable (if EXIT_FLAG is set to true => the program exit with value) (else => Do nothing).
// third Argument: exit value.
void    errorStream(std::string description, bool EXIT_FLAG, int value);
/*
** PARSING FUNCTIONS:
*/
// main function (PARSING CONFIGFILE):
std::vector<ServConfig>     confParsing(std::string configFILE);
void    OUT_Position(std::string &FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI);
// void    SERVER_Position(std::string FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI);
// void    LOCATION_Position(std::string FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI);
// void    CGI_Position(std::string FILE, std::string::iterator &it, std::vector<ServConfig> &vect, int *whereAmI);
bool    isEmptyLine(std::string LINE);

#endif
