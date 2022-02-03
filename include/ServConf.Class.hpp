/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServConf.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:22:45 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/03 21:15:12 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVCONF_CLASS_HPP
#define SERVCONF_CLASS_HPP

#include "Location.Class.hpp"
/*
** DEFAULT CONFIGFILE: *********************************************************
** No write permission: -r--r--r--  conf/default.conf
*/
# define DFLTCONF   "./conf/default.conf"

/*
** CONFIGFILE  KEYWORDS: *******************************************************
*/
# define KW_SERVER              "server"
# define KW_SERVER_NAME         "server_name"           //  Server_name
# define KW_ERR_PAGE            "error_page"            //  Default error pages
# define KW_CLIENT_BODY_SIZE    "client_max_body_size"  //  Limit client body size
# define KW_ACCEPTED_METHOD     "allow_methods"         //  Define a list of accepeted HTTP Methods
# define KW_AUTOINDEX           "autoindex"             //  Turn on or off directory listing
# define KW_DEFAULT_FILE        "index"                 //  Default file to answer if the request is a directory
# define KW_LOCATION            "location"              //  Define a directory or a file from where the file should be search
# define KW_LOCATION_ROOT       "root"                  //  The KW_LOCATION is rooted to KW_LOCATION_ROOT

class ServConfig
{
private:
    /* data */
public:
    ServConfig(/* args */){}
    ~ServConfig(){}
};

#endif
