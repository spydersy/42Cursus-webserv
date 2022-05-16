#include "Request.hpp"

Request::Request () {
	this->_bodyfilename = "/var/tmp/request_" + randomfilename("") + "_body";
	this->_request_type = UNKNOWN;
	this->_contentLength = 0;
	this->_totalread = 0;
	this->_bodyFileFD = -1;
	this->_fileOpened = false;
	this->_CRLF = true;
	this->_last_update = time(NULL);
}

Request::Request (const Request &rqst ) {
	*this = rqst;
}

Request::~Request () {
	this->_bodyfilename = "";
	this->_bodyFileFD = -1;
	this->_request_type = UNKNOWN;
	this->_contentLength = 0;
	this->_totalread = 0;
	this->_fileOpened = false;
	this->_CRLF = true;
	this->_last_update = time(NULL);
}

Request	&Request::operator= ( const Request &rqst ) {
	this->_rqstLexer = rqst._rqstLexer;
	this->_method = rqst._method;
	this->_path = rqst._path;
	this->_query_string = rqst._query_string;
	this->_version = rqst._version;
	this->_host = rqst._host;
	this->_port = rqst._port;
	this->_headers = rqst._headers;
	this->_bodyfilename = rqst._bodyfilename;
	this->_bodyFileFD = rqst._bodyFileFD;
	this->_fileOpened = rqst._fileOpened;
	this->_totalread = rqst._totalread;
	this->_contentLength = rqst._contentLength;
	this->_request_type = rqst._request_type;
	this->_chunked = rqst._chunked;
	this->_CRLF = rqst._CRLF;
	this->_last_update = rqst._last_update;

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
	if (this->_rqstLexer.getLineSet() == true && this->_rqstLexer.getHeadersSet() == true) {
		// here test how to write in file
		if (this->_request_type == UNKNOWN) {
			if (this->_rqstLexer.getHeaders().find("Transfer-Encoding:") != std::string::npos)
				this->_request_type = CHUNKED;
			else if(this->_rqstLexer.getHeaders().find("Content-Length:") != std::string::npos)
				this->_request_type = LENGTH;
			else {
				this->_request_type = NONE;	// Bad Request	BAD_REQUEST
				retVal = BAD_REQUEST;
			}
		}
		if (this->_fileOpened == false && this->_bodyFileFD == -1 && this->_request_type != UNKNOWN && this->_request_type != NONE) {
			this->_bodyFileFD = open(this->_bodyfilename.c_str(), O_WRONLY | O_CREAT | O_APPEND, S_IWUSR | S_IRUSR);
			if (this->_bodyFileFD == -1) {
				std::cerr << "Couldn't Open File" << std::endl;
			}
			this->_fileOpened = true;
		}
		if (this->_request_type == CHUNKED && this->_fileOpened == true) {
			retVal = !read_chunked(bufferString);
		}
		else if (this->_request_type == LENGTH && this->_fileOpened == true) {
			retVal = !read_content_length(bufferString);
		}
		this->_last_update = time(NULL);
	}
	if (bufferString.empty() && this->_request_type == NONE) {
		retVal = FINISHED;
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
	if (buffer.length() > 0) {
		this->_totalread += buffer.length();
		write_select(this->_bodyFileFD, buffer, buffer.length());
	}
	if (this->_totalread >= this->_contentLength)
	{
		close(this->_bodyFileFD);
		return true ;
	}
	return false;
}

bool	Request::getChunkSize()
{
	std::string number;
	size_t	i = 0;
	for (std::string::iterator it = _chunked.begin(); it != _chunked.end(); it++)
	{
		if (isHex((*it)) == false)
			break;
		number += *it;
		i++;
	}
	if (this->_chunked.size() < i + 1 || (this->_chunked[i] != '\r' && this->_chunked[i + 1] != '\n')) {
		this->_totalread = 0;
		return false;
	}
	if (!number.empty())
	{
		std::istringstream(number) >> std::hex >> this->_totalread;
		this->_chunked.erase(0, i);
		if (this->_totalread != 0) {
			if (this->_chunked.length() >= 2) {
				if (this->_chunked[0] == '\r' && this->_chunked[1] == '\n')
					this->_chunked.erase(0, 2);
			}
			else {
				this->_CRLF = false;
				return false;
			}
		}
		else 
			this->_chunked.erase(0, i + 4);
	}
	return true;
}

bool	Request::add_chunk() {
	if (this->_totalread > this->_chunked.length()) {
		write_select(this->_bodyFileFD, this->_chunked, this->_chunked.length());
		this->_contentLength += this->_chunked.length();
		this->_totalread -= this->_chunked.length();
		this->_chunked.erase(0, this->_chunked.length());
		return false;
	}
	else {
		write_select(this->_bodyFileFD, this->_chunked, this->_totalread);
		this->_contentLength += this->_totalread;
		this->_chunked.erase(0, this->_totalread);
		this->_totalread = 0;
		if (this->_chunked.length() >= 2) {
			if (this->_chunked[0] == '\r' && this->_chunked[1] == '\n')
				this->_chunked.erase(0, 2);
		}
		else {
			this->_CRLF = false;
			return false;
		}
		return true;
	}
}

bool		Request::read_chunked( std::string &buffer )
{
	this->_chunked += buffer;
	if (this->_CRLF == false) {
		if (this->_chunked.length() >= 2 && this->_chunked[0] == '\r' && this->_chunked[1] == '\n') {
			this->_CRLF = true;
			this->_chunked.erase(0, 2);
		}
	}
	while (!this->_chunked.empty()) {
		if (this->_totalread == 0) {
			if (getChunkSize() == false)
				return false;
			if (this->_totalread != 0) {
				if (add_chunk() == false)
					return false;
			}
			else if (this->_chunked.empty()) {
				close(this->_bodyFileFD);
				return true;
			}
		}
		else {
			if (add_chunk() == false)
				return false;
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
}

void		Request::setHost() {
	for (std::vector< std::pair<std::string, std::string> >::iterator it = this->_headers.begin();
	it != this->_headers.end(); it++) {
		if (it->first == "Host") {
			size_t found = it->second.find(":");
			if (found != std::string::npos) {
				this->_host = it->second.substr(0, it->second.find(":"));
				setPort(it->second.substr(it->second.find(":") + 1));
			}
			else
			{
				this->_host = std::string(it->second);
				setPort("");
			}
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

size_t			&Request::getContentLength() {
	return this->_contentLength;
}

time_t			&Request::getLastUpdate() {
	return this->_last_update;
}

std::string	Request::getHeaders( std::string KEY)
{
	for (std::vector< std::pair<std::string, std::string> >::iterator it = _headers.begin();
		it != _headers.end(); it++)
	{
		if (it->first.compare(KEY) == 0)
			return it->second;
	}
	return "";
}