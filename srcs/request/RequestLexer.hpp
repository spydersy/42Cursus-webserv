#ifndef REQUESTLEXER_HPP
#define REQUESTLEXER_HPP
#include "Utils.hpp"
#define RECV_SIZE 4096

class RequestLexer {
	std::string		_filename;
	std::string		_requestLine;
	bool			_lineSet;
	std::string		_headers;
	bool			_headersSet;
	std::ofstream	_rqstFile;
	size_t			_totalread;

	public:
		char			buffer[RECV_SIZE + 1];
		RequestLexer();
		~RequestLexer();

		// Getters
		std::string		&getFilename();
		std::string		&getRequestLine();
		bool			&getLineSet();
		std::string		&getHeaders();
		bool			&getHeadersSet();
		size_t			&getTotalread();

		void			add_buffer( int &recvLength );
		void			check_requestLine();
		void			check_headers();
		void			read_content_length( int &newSockfd );
		void			read_chunked( int &newSockfd );
};

#endif