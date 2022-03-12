/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.Class.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 19:57:42 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/01 02:44:39 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_CLASS_HPP
#define LOCATION_CLASS_HPP

#include "Server.Class.hpp"
#include <iostream>
#include <vector>

# define METH_GET           1
# define METH_POST          10
# define METH_DELETE        100

class Location
{
private:
    const std::string           _whoAmI;
    std::string                 _locations_path;
    std::vector<std::string>    _methods;
    std::string                 _root;
    std::string                 _client_max_body_size;
    std::vector<std::string>    _index;
    std::string                 _autoindex;
public:
    // CONTRUCTORS & DESTRUCTORS : 
    Location();
    ~Location();
    Location    &operator=( const Location &src);

    // GETTERS : 
    std::string                 &get_locations_path();
    std::vector<std::string>    &get_methods();
    std::string                 &get_root();
    std::string                 &get_autoindex();
    std::string                 &get_client_max_body_size();
    std::vector<std::string>    &get_index();
    std::string                 getId() const ;
};

#endif
