/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.Class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/01 02:47:34 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** CONSTRUCTORS & DESTRUCTORS : 
*/
Location::Location() :  _whoAmI("Location"),
                        
                        _locations_path(""),
                        _methods(std::vector<std::string>()),
                        _root(""),
                        _client_max_body_size(""),  
                        
                        _index(std::vector<std::string>()),
                        _autoindex("") {}
Location::~Location() {}

Location    &Location::operator=( const Location &src) {
    this->_locations_path = src._locations_path;
    this->_methods = src._methods;
    this->_root = src._root;
    this->_client_max_body_size = src._client_max_body_size;
    this->_index = src._index;
    this->_autoindex = src._autoindex;
    return *this;
}

/*
** GETTERS : 
*/
std::string                 &Location::get_locations_path() { return this->_locations_path; }
std::vector<std::string>    &Location::get_methods() { return this->_methods; }
std::string                 &Location::get_root() { return this->_root; }
std::string                 &Location::get_autoindex() { return this->_autoindex; }
std::string                 &Location::get_client_max_body_size() { return this->_client_max_body_size; }
std::vector<std::string>    &Location::get_index() { return this->_index; }
std::string                 Location::getId() const { return this->_whoAmI; }
