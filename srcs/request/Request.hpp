#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <sstream>
#include "Utils.hpp"
#include "RequestLexer.hpp"

/*
** HOW TO READ THE REQUEST: **************************************************************
*/

#define UNKNOWN 0
#define LENGTH 1
#define CHUNKED 2
#define NONE 3

/**
 * if add_buffer failed bcs of neither content_length or transfer_encoding was specified
 * add_buffer return BAD_REQUEST value
 * else if request not finished yet returns NOT_FINISHED
 * else if request is FINISHED returns FINISHED
 */

#define WRITE_FAILED -1
#define FINISHED 0
#define NOT_FINISHED 1
#define BAD_REQUEST 2

/**
 * class Request
 */

class Request {
	public:
		typedef std::pair<std::string, std::string>		string_pair;
    private:
		RequestLexer									_rqstLexer;			// Reading Only
		std::string										_method;
		std::string										_path;
		std::string										_query_string;
		std::string										_version;
		std::string										_host;
		int												_port;
        std::vector<string_pair>						_headers;
		std::string										_bodyfilename;		// make sure to remove it after use
		int												_bodyFileFD;
		bool											_fileOpened;		// Reading Only
		size_t											_totalread;			// Reading Only
		size_t											_contentLength;		// Reading Only
		int												_request_type;		// Reading Only
		std::string										_chunked;
		bool											_CRLF;
		time_t											_last_update;

		// private methods
		void											add_request_line ( std::string &buffer );
		void											add_headers ( std::string &buffer );
		bool											read_content_length( std::string &buffer );
		bool											read_chunked( std::string &buffer );
		bool											getChunkSize();
		bool											add_chunk();
	public:
		Request ();
		Request ( const Request &rqst );
		~Request ();
		Request											&operator= ( const Request &rqst );
		// add Buffer to right place
		int												add_buffer ( int &recvLength, char *add_buffer );
		// Setters
		void											setMethod ( std::string &part );
		void											setPath ( std::string &part );
		void											setQueryString ( std::string &part );
		void											setVersion ( std::string &part );
		void											setHostHeaders();
		void											setHost ();
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
		size_t											&getContentLength();
		time_t											&getLastUpdate();
		std::string										getHeaders( std::string KEY);
};

#endif
