/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MimeTypes.Class.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/14 01:04:42 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/18 13:26:13 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIMETYPES_CLASS_HPP
#define MIMETYPES_CLASS_HPP

#include <iostream>
#include "./webserv.hpp"

class MimeTypes
{
private:
    void                                                initMimeTypes();
    std::string                                         _path;
    std::vector<std::pair<std::string, std::string> >   _types;
    std::pair<std::string, std::string>                 _mimetype;
    std::string                                         _extension;
    std::string                                         _contentType;
public:
    // CONSTRUCTORS & DESTRUCTORS :
    ~MimeTypes();
    MimeTypes( void );
    MimeTypes(std::string PATH);

    // GETTERS :
    std::string getExtension();
    std::pair<std::string, std::string> get_mimetype();

    // SETTERS:
    void        set_path(std::string path);
    // METHODS :
    size_t      haveExtension();
    bool        badExtension();
};

#endif
