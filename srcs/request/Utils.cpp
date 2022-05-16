#include "Utils.hpp"

std::string	current_time_stamp( void )
{
	time_t ttime = std::time(0);
	std::string time(std::to_string(ttime));
	return	time;
}

std::string					randomfilename( std::string str ) {
	static int a = 1;
	time_t ttime = std::time(0);
	std::string filename(std::to_string(ttime));
	filename.insert(filename.length(), std::to_string(a) + "_" + str);
	a++;
	return (filename);
}

std::string					trimString( std::string str, char c )
{
	for (std::string::iterator it = str.begin(); *it == c; it++) {
        str.erase(it);
        it = str.begin();
    }
    if (*(str.begin()) == c)
        str.erase(str.begin());
    for (std::string::iterator it = str.end() - 1; *it == c; it--) {
        str.erase(it);
    }
	return (str);
}

std::vector< std::string >	StringSplit( std::string str, std::string delimiter ) {
	std::vector<std::string> parts;
	while (str.length() && str.find(delimiter) != std::string::npos) {
		std::string tmp = str.substr(0, str.find(delimiter));
			parts.push_back(tmp);
		str.erase(0, str.find(delimiter) + delimiter.length());
	}
	parts.push_back(str);
	return parts;
}

bool						isHex( char c )
{
	std::string hex("0123456789abcdefABCDEF");
	if (hex.find(c) != std::string::npos) {
		return true;
	}
	return false;
}

// write with Select
int						write_select (int fd, std::string &buffer, size_t size) {
	fd_set	wset;

	FD_ZERO(&wset);
	FD_SET(fd, &wset);
	int status = select(fd + 1, NULL, &wset, NULL, NULL);
	if (status < 0) {
		std::cerr << "Select Failed!" << std::endl;
		return -1;
	}
	if (FD_ISSET(fd, &wset)) {
		int ret = write(fd, buffer.c_str(), size);
		return ret;
	}
	return -1;
}

// read with Select
int						read_select (int fd, std::string &buffer, size_t size) {

	char buff[size + 1];
	fd_set	rset;
	int read_ret = 0;

	FD_ZERO(&rset);
	FD_SET(fd, &rset);
	int status = select(fd + 1, &rset, NULL, NULL, NULL);
	if (status < 0)
		std::cerr << "Select Failed!" << std::endl;
	if (FD_ISSET(fd, &rset))
	{
		read_ret = read(fd, buff, size);
		if (read_ret > 0)
		{
			buff[read_ret] = '\0';
			buffer = std::string(buff, read_ret);
		}
	}
	return read_ret;
}