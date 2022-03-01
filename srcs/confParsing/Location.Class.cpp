/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.Class.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:14:29 by abelarif          #+#    #+#             */
/*   Updated: 2022/02/28 23:16:32 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"

/*
** CONSTRUCTORS & DESTRUCTORS : 
*/
Location::Location() :  _locations_path(""),
                        _methods(std::vector<std::string>()),
                        _root(""),
                        _client_max_body_size(""),  
                        _index(std::vector<std::string>()),
                        _autoindex("") {}
Location::~Location() {}

/*
** GETTERS : 
*/
std::string                 &Location::get_locations_path() { return this->_locations_path; }
std::vector<std::string>    &Location::get_methods() { return this->_methods; }
std::string                 &Location::get_root() { return this->_root; }
std::string                 &Location::get_autoindex() { return this->_autoindex; }
std::string                 &Location::get_client_max_body_size() { return this->_client_max_body_size; }
std::vector<std::string>    &Location::get_index() { return this->_index; }