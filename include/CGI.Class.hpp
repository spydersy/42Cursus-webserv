/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CGI.Class.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 16:39:45 by abelarif          #+#    #+#             */
/*   Updated: 2022/04/23 05:25:15 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGI_CLLASS_HPP
#define CGI_CLLASS_HPP

#include "webserv.hpp"

class Request;
class Response;

class CGI
{
    private:
        std::string                     _extention;
        std::string                     _cgi_path;
        std::vector<std::string>        _methods;
        char**                          _envp;
        char**                          _argv;
        std::string                     _cgi_response_file;
        std::string                     _status;
        std::string                     _header;
        std::string                     _FILEINLINE;

        std::string                     header_to_envp(std::pair<std::string, std::string>);
        std::string                     generate_uri(Request request);
        void                            set_header(Response & response);
        void                            set_envp(Request request, Response response);
        std::string                     set_cgi_path( void );
        void                            set_argv(Response response);
        std::string                     set_cgi_response_file( void );
        std::string                     init_data();
        size_t                          getAccessType(std::string PATH);
        std::string                     cgi_process( Response & response, Request request );
		std::string					    set_status( void );

    public:
    // Canonical Form:
        CGI( void );
        ~CGI();
        CGI( const CGI &src);
        CGI &operator=(const CGI &src);

    // Getters:
    std::string                 &get_extention( void );
    std::string                 &get_cgi_response_file( void );
    std::string                 &get_cgi_path( void );
    std::vector<std::string>    &get_methods( void );
    std::string                 get_script_name(Response response);
    std::string                 get_path_info(Response response);
    // Methods:
    std::string                         execute_cgi(Request request, Response & response);
    void                         fillResponseBuffer( Response & response );
};



#endif