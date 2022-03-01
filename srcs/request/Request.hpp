#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include "Utils.hpp"
#include "RequestLexer.hpp"

#define UNKNOWN 0
#define LENGTH 1
#define CHUNKED 2
#define NONE 3

class Request {
    private:
        typedef std::pair<std::string, std::string>		string_pair;
		RequestLexer									_rqstLexer;
		std::string										_method;
		std::string										_path;
		std::string										_query_string;
		std::string										_version;
		std::string										_host;
		int												_port;
        std::vector<string_pair>						_headers;
		std::string										_bodyfilename;
		std::ofstream									_bodyFile;
		bool											_fileOpened;
		size_t											_totalread;
		size_t											_contentLength;
		int												_request_type;
		bool											_error;

		// private methods
		int												read_content_length( std::string &buffer );
		int												read_chunked( std::string &buffer );
	public:
		Request ();
		Request ( const Request &rqst );
		~Request ();
		Request											&operator= ( const Request &rqst );
		// add Buffer to right place
		int												add_buffer ( int &recvLength, char *add_buffer );
		void											add_request_line ( std::string &buffer );
		void											add_headers ( std::string &buffer );
		// Setters
		void											setMethod ( std::string &part );
		void											setPath ( std::string &part );
		void											setQueryString ( std::string &part );
		void											setVersion ( std::string &part );
		void											setHostHeaders();
		void											setHost ( std::string hostString );
		void											setPort ( std::string  portString );
		void											setHeaders ();
		void											addHeader ( std::string header );
		void											setBodyfile ( std::string filename );

		// Lexer to parser
		void											Lexer_to_parser ();
		
		// Getters
		RequestLexer									&getRequestLexer();
		std::string										&getMethod ();
		std::string										&getPath ();
		std::string										&getQueryString ();
		std::string										&getVersion ();
		std::string										&getHost ();
		int												&getPort ();
		std::vector<string_pair>						&getHeaders ();
		std::string										&getBodyfilename ();
		size_t											&getTotalread();
};

std::ostream & operator<<( std::ostream & o, Request & rqst );

#endif