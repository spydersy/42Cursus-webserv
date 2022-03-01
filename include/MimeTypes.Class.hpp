/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypes.Class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:04:42 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/28 23:24:48 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIMETYPES_CLASS_HPP
#define MIMETYPES_CLASS_HPP

#include <iostream>
#include "./webserv.hpp"

class MimeTypes
{
private:
    Request                                             _REQUEST;
    std::vector<Server>                                              _CONF;
    std::vector<std::pair<std::string, std::string> >   _types;
    std::pair<std::string, std::string>                 _mimetype;
    std::string                                         _extension;
    std::string                                         _contentType;
public:
    // CONSTRUCTORS & DSTRUCTORS : 
    ~MimeTypes();
    MimeTypes(Request REQUEST, std::vector<Server> CONF);

    // GETTERS : 
    std::string getExtension();
    std::pair<std::string, std::string> get_mimetype();

    // METHODS : 
    size_t    haveExtension();
    bool    badExtension();
};

#endif
