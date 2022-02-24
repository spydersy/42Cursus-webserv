#include "RequestLexer.hpp"

RequestLexer::RequestLexer() {
	this->_requestLine = "";
	this->_headers = "";
	this->_filename = "/var/tmp/request_" + randomfilename("") + "_body";
	this->_lineSet = false;
	this->_headersSet = false;
	this->_totalread = 0;
}

RequestLexer::~RequestLexer() {
	remove(this->_filename.c_str());
}

std::string		&RequestLexer::getFilename() {
	return this->_filename;
}

std::string		&RequestLexer::getRequestLine() {
	return this->_requestLine;
}

bool			&RequestLexer::getLineSet() {
	return this->_lineSet;
}

std::string		&RequestLexer::getHeaders() {
	return this->_headers;
}

bool			&RequestLexer::getHeadersSet() {
	return this->_headersSet;
}

size_t			&RequestLexer::getTotalread() {
	return this->_totalread;
}

void	RequestLexer::add_buffer( int &recvLength ) {
	if (this->_lineSet == false) {
		this->_requestLine.resize(this->_requestLine.length() + recvLength);
		this->_requestLine.append(this->buffer, recvLength);
	}
	else if (this->_headersSet == false) {
		this->_headers.resize(this->_headers.length() + recvLength);
		this->_headers.append(this->buffer, recvLength);
	}
	else {
		this->_rqstFile.write(this->buffer, recvLength);
	}
}

void	RequestLexer::check_requestLine() {
	size_t	found;
	if (this->_lineSet == false) {
		if ((found = this->_requestLine.find("\r\n")) != std::string::npos)
		{
			this->_headers.resize(this->_headers.length() + this->_requestLine.length() - found - 2);
			this->_headers.append(this->_requestLine, found + 2, this->_requestLine.length() - found - 2);
			this->_requestLine.resize(found);
			this->_lineSet = true;
		}
	}
}

void	RequestLexer::check_headers() {
	size_t	found;
	if (this->_headersSet == false) {
		if ((found = this->_headers.find("\r\n\r\n")) != std::string::npos)
		{
			this->_rqstFile.write(this->_headers.c_str() + found + 4, this->_headers.length() - found - 4);
			this->_totalread += this->_headers.length() - found - 4;
			this->_headers.resize(found);
			this->_headersSet = true;
		}
	}
}

void	RequestLexer::read_content_length( int &newSockfd ) {
	int				recvLength;
	size_t          content_length = stoi(this->_headers.substr(this->_headers.find("Content-Length:") + 16));
	
	this->_rqstFile.open(this->_filename, std::ofstream::out);
	while ((recvLength = recv(newSockfd, &this->buffer, RECV_SIZE, 0))) {
		this->buffer[recvLength] = '\0';
		this->_totalread += recvLength;
		this->_rqstFile.write(this->buffer, recvLength);
		if (this->_totalread >= content_length)
			break ;
	}
}

void    RequestLexer::read_chunked( int &newSockfd ) {
	std::string     combin;
	int				recvLength;
	
	this->_rqstFile.open(this->_filename, std::ofstream::out);
	while ((recvLength = recv(newSockfd, &this->buffer, RECV_SIZE, 0))) {
		this->buffer[recvLength] = '\0';
		this->_totalread += recvLength;
		this->_rqstFile.write(this->buffer, recvLength);
		if (std::string(this->buffer).find("\r\n\r\n") != std::string::npos)
			break;
		else if (combin != "") {
			combin += std::string(this->buffer, 0, recvLength);
			if (std::string(this->buffer).find("\r\n\r\n") != std::string::npos) {
				break ;
			} else {
				combin = combin.substr(combin.length() - 5);
			}
		}
		else {
			combin = std::string(this->buffer, recvLength - 5, 5);
		}
	}
}