/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 02:02:24 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/03 21:15:36 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
#define WEBSERV_HPP

#include "ServConf.Class.hpp"
#include <iostream>
#include <fstream>

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

// first Argument : String variable That describe the error.
// second Argument: bool variable (if EXIT_FLAG is set to true => the program exit with value) (else => Do nothing).
// third Argument: exit value.
void    errorStream(std::string description, bool EXIT_FLAG, int value);

// main function (PARSING CONFIGFILE):
std::vector<ServConfig>    confParsing(std::string configFILE);

#endif
