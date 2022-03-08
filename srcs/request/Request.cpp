#include "Request.hpp"

Request::Request (): _error(false) {
	this->_bodyfilename = "/var/tmp/request_" + randomfilename("") + "_body";
	this->_request_type = UNKNOWN;
	this->_contentLength = 0;
	this->_totalread = 0;
	this->_fileOpened = false;
}

Request::Request (const Request &rqst ) {
	*this = rqst;
	this->_request_type = UNKNOWN;
	this->_contentLength = 0;
	this->_totalread = 0;
	this->_fileOpened = false;
}

Request::~Request () {
	remove(this->_bodyfilename.c_str());
	this->_bodyfilename = "";
	this->_request_type = UNKNOWN;
	this->_contentLength = 0;
	this->_totalread = 0;
	this->_fileOpened = false;
}

Request	&Request::operator= ( const Request &rqst ) {
	this->_method = rqst._method;
	this->_path = rqst._path;
	this->_query_string = rqst._query_string;
	this->_version = rqst._version;
	this->_host = rqst._host;
	this->_port = rqst._port;
	this->_headers = rqst._headers;
	this->_bodyfilename = rqst._bodyfilename;
	this->_error = rqst._error;

	return *this;
}

// add Buffer to right place
int		Request::add_buffer( int &recvLength, char *buffer ) {
	bool	retVal = false;
	std::string	bufferString(buffer, recvLength);
	if (this->_rqstLexer.getLineSet() == false) {
		add_request_line(bufferString);
	}
	if (this->_rqstLexer.getHeadersSet() == false && this->_rqstLexer.getLineSet() == true) {
		add_headers(bufferString);
	}
	if (bufferString.empty()) {
		retVal = true;
	}
	else if (this->_rqstLexer.getLineSet() == true && this->_rqstLexer.getHeadersSet() == true) {
		// here test how to write in file
		if (this->_request_type == UNKNOWN) {
			if(this->_rqstLexer.getHeaders().find("Content-Length:") != std::string::npos)
				this->_request_type = LENGTH;
			else if (this->_rqstLexer.getHeaders().find("Transfer-Encoding:") != std::string::npos)
				this->_request_type = CHUNKED;
			else
				this->_request_type = NONE;
		}
		if (this->_fileOpened == false) {
			this->_bodyFile.open(this->_bodyfilename, std::ofstream::out);
			this->_fileOpened = true;
		}
		if (this->_request_type != UNKNOWN && this->_request_type != NONE && this->_fileOpened == true) {
			if (this->_request_type == LENGTH)
				retVal = read_content_length(bufferString);
			else
				retVal = read_chunked(bufferString);
		}
	}
	return retVal;
}

void	Request::add_request_line( std::string &buffer ) {
	size_t	found;
	if ((found = buffer.find("\r\n")) != std::string::npos)
	{
		this->_rqstLexer.getRequestLine() += buffer.substr(0, found);
		buffer = buffer.substr(found + 2);
		this->_rqstLexer.setLineSet();
	}
	else {
		this->_rqstLexer.getRequestLine() += buffer;
	}
}

void	Request::add_headers( std::string &buffer ) {
	size_t	found;
	if ((found = buffer.find("\r\n\r\n")) != std::string::npos)
	{
		this->_rqstLexer.getHeaders() += buffer.substr(0, found);
		buffer = buffer.substr(found + 4);
		this->_rqstLexer.setHeadersSet();
	}
	else {
		this->_rqstLexer.getHeaders() += buffer;
	}
}


bool		Request::read_content_length( std::string &buffer )
{
	if (this->_contentLength == 0) {
		size_t found = this->_rqstLexer.getHeaders().find("Content-Length:");
		std::string content = this->_rqstLexer.getHeaders().substr(found + 16);
		this->_contentLength = std::stol(content);
	}
	this->_totalread += buffer.length();
	this->_bodyFile.write(buffer.c_str(), buffer.length());
	if (this->_totalread >= this->_contentLength) 
	{
		this->_bodyFile.close();
		return true ;
	}
	return false;
}

void	Request::getChunkSize()
{
	std::string number;
	int	i = 0;
	for (std::string::iterator it = _chunked.begin(); it != _chunked.end(); it++)
	{
		if (isHex((*it)) == false)
			break;
		number += *it;
		i++;
	}
	if (!number.empty())
	{
		std::istringstream(number) >> std::hex >> this->_totalread;
		if (this->_totalread != 0) {
			if (this->_chunked[i] == '\r' && this->_chunked[i + 1] == '\n')
				this->_chunked.erase(0, i + 2);
			else
				this->_chunked.erase(0, i);
		}
		else 
			this->_chunked.erase(0, i + 4);
	}
}

bool		Request::read_chunked( std::string &buffer )
{
	this->_chunked += buffer;
	while (!this->_chunked.empty()) {
		if (this->_totalread == 0) {
			getChunkSize();
			if (this->_totalread != 0) {
				if (this->_totalread > this->_chunked.length()) {
					this->_bodyFile.write(this->_chunked.c_str(), this->_chunked.length());
					this->_contentLength += this->_chunked.length();
					this->_totalread -= this->_chunked.length();
					this->_chunked.erase(0, this->_chunked.length());
					return false;
				}
				else {
					this->_bodyFile.write(this->_chunked.c_str(), this->_totalread);
					this->_contentLength += this->_totalread;
					this->_chunked.erase(0, this->_totalread + 2);
					this->_totalread = 0;
				}
			}
			else if (this->_chunked.empty()) {
				this->_bodyFile.close();
				return true;
			}
		}
		else {
			if (this->_totalread > this->_chunked.length()) {
				this->_bodyFile.write(this->_chunked.c_str(), this->_chunked.length());
				this->_contentLength += this->_chunked.length();
				this->_totalread -= this->_chunked.length();
				this->_chunked.erase(0, this->_chunked.length());
				return false;
			}
			else {
				this->_bodyFile.write(this->_chunked.c_str(), this->_totalread);
				this->_contentLength += this->_totalread;
				this->_chunked.erase(0, this->_totalread + 2);
				this->_totalread = 0;
			}
		}
	}
	return false;
}

// Setters

void		Request::setMethod ( std::string &part ) {
	this->_method = part;
}

void		Request::setPath ( std::string &part ) {
	if (part.find("?") != std::string::npos) {
		this->_path = part.substr(0, part.find("?"));
		part.erase(0, part.find("?"));
	}
	else {
		this->_path = part;
	}
}

void		Request::setQueryString ( std::string &part ) {
	if (part.find("?") != std::string::npos) {
		this->_query_string = part.substr(part.find("?") + 1);
		part.erase(part.find("?") + 1);
	}
}

void		Request::setVersion ( std::string &part ) {
	if (part.length() > 0) {
		this->_version = part;
	}
	else {
		this->_error = true;
	}
}

void		Request::setHost() {
	for (std::vector< std::pair<std::string, std::string> >::iterator it = this->_headers.begin();
	it != this->_headers.end(); it++) {
		if (it->first == "Host") {
			this->_host = it->second.substr(0, it->second.find(":"));
			setPort(it->second.substr(it->second.find(":") + 1));
			break;
		}
	}
}

void		Request::setPort ( std::string  portString ) {
	if (portString != "") {
		this->_port = std::stoi(portString);
	}
	else {
		this->_port = 80;
	}
}

void		Request::setHeaders() {
	std::vector< std::string > headers = StringSplit(this->_rqstLexer.getHeaders(), "\r\n");
	for (std::vector< std::string >::iterator it = headers.begin(); it != headers.end(); it++) {
		addHeader((*it));
	}
}

void		Request::addHeader ( std::string header ) {
	std::string key = header.substr(0, header.find(":"));
	std::string value = header.substr(header.find(":") + 1);
	value = trimString(value, ' ');
	this->_headers.push_back(std::make_pair(key, value));
}

void		Request::setBodyfile ( std::string filename ) {
	this->_bodyfilename = filename;
}

/* 
 *	Lexer to parser
 *  Convert The RequestLexer Class to Request Class
 * 	and extract all of the method, path, query string and version from rqstLine
 * 	also headers from RequestLexer.headers
*/
void			Request::Lexer_to_parser () {
	std::vector< std::string > parts = StringSplit(this->_rqstLexer.getRequestLine(), " ");
	if (parts.size() == 3) {
		setMethod(parts[0]);
		setPath(parts[1]);
		setQueryString(parts[1]);
		setVersion(parts[2]);
	}
	setHeaders();
	setHost();
}

// Getters
RequestLexer	&Request::getRequestLexer() {
	return this->_rqstLexer;
}

std::string		&Request::getMethod () {
	return this->_method;
}

std::string		&Request::getPath () {
	return this->_path;
}

std::string		&Request::getQueryString () {
	return this->_query_string;
}

std::string		&Request::getVersion () {
	return this->_version;
}

std::string		&Request::getHost () {
	return this->_host;
}

int				&Request::getPort () {
	return this->_port;
}

std::vector< std::pair<std::string, std::string> >	&Request::getHeaders () {
	return this->_headers;
}

std::string		&Request::getBodyfilename () {
	return this->_bodyfilename;
}

size_t			&Request::getTotalread() {
	return this->_totalread;
}

std::ostream & operator<<( std::ostream & o, Request & rqst ) {
	o << "Request:" << "\n";
	o << "Host: " << rqst.getHost() << ", Port: " << rqst.getPort() << "\n";
	o << "Method: " << rqst.getMethod() << ", Path: " << rqst.getPath() << ", Version: " << rqst.getVersion() << "\n";
	if (!rqst.getQueryString().empty()) {
		o << "QuesryString: " << rqst.getQueryString() << "\n";
	}
	std::vector< std::pair<std::string, std::string> > headers = rqst.getHeaders();
	for (std::vector< std::pair<std::string, std::string> >::iterator it = headers.begin(); it != headers.end(); it++) {
		o << it->first << ", " << it->second << "\n";
	}
	return o;
}