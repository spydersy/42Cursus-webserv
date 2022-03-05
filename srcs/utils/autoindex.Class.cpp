/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   autoindex.Class.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/05 16:03:40 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/05 16:22:53 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/webserv.hpp"


/*
** Getters & Setters :  
*/
autoindex::autoindex( std::string path) :   _path(path),
                                            _page("") {
    this->_page.append("<html>\r\n");
    this->_page.append(" <style>\r\n");
    this->_page.append(" th {\r\n");
    this->_page.append("     text-align: left;\r\n");
    this->_page.append(" }\r\n");
    this->_page.append(" </style>\r\n");
    this->_page.append("<head><title>Index of " + this->_path + "</title></head>\r\n");
    this->_page.append("<body>\r\n");
    this->_page.append("<h1>Index of " + this->_path + "</h1><hr><pre>\r\n");
    this->_page.append("<table style=\"width:100%\">\r\n");
    this->_page.append("<tr>\r\n");
    this->_page.append("<th>Name</th>\r\n");
    this->_page.append("<th>Size</th>\r\n");
    this->_page.append("<th>Date</th>\r\n");
    this->_page.append("</tr>\r\n");
    generatePage();
}
autoindex::~autoindex(){}
/*
** Getters :
*/
std::string autoindex::get_page() { return this->_page; }

/*
** Methods :
*/

int     autoindex::getFileSize( std::string file) {
    std::ifstream in_file(file.c_str(), std::ios::binary);

    in_file.seekg(0, std::ios::end);
    int file_size = in_file.tellg();
    return (file_size);
}

std::string autoindex::getFileDate(std::string file) {
    struct stat t_stat;

    stat(file.c_str(), &t_stat);
    struct tm * timeinfo = localtime(&t_stat.st_ctime);
    std::string date = asctime(timeinfo);
    if (date.length() != 0) {
        date.erase(date.begin() + date.length() - 1);
    }
    return date;
}

std::string     autoindex::getFilePermissions(std::string file) {
    struct stat     st;
    std::string     modeval;

    if(stat(file.c_str(), &st) == 0){
        mode_t perm = st.st_mode;
        modeval.push_back((perm & S_IRUSR) ? 'r' : '-');
        modeval.push_back((perm & S_IWUSR) ? 'w' : '-');
        modeval.push_back((perm & S_IXUSR) ? 'x' : '-');
        modeval.push_back((perm & S_IRGRP) ? 'r' : '-');
        modeval.push_back((perm & S_IWGRP) ? 'w' : '-');
        modeval.push_back((perm & S_IXGRP) ? 'x' : '-');
        modeval.push_back((perm & S_IROTH) ? 'r' : '-');
        modeval.push_back((perm & S_IWOTH) ? 'w' : '-');
        modeval.push_back((perm & S_IXOTH) ? 'x' : '-');
        return modeval;     
    }
    else{
        return strerror(errno);
    }   
}

void    autoindex::generatePage(){
    DIR                 *d;
    struct dirent       *dir;
    std::string         path(this->_path);

    d = opendir(path.c_str());
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            this->_page.append("<tr>\r\n");
            this->_page.append("<td><a href=\"" + path + dir->d_name + "\">" + dir->d_name + "</a></td>\r\n");
            this->_page.append("<td>" + std::to_string(getFileSize(path + "/" + dir->d_name)) + "</td>\r\n");
            this->_page.append("<td>" + getFileDate(path + "/" + dir->d_name) +"</td>");
            this->_page.append("</tr>");
        }
        closedir(d);
    }
    this->_page.append("</pre><hr></body>\r\n");
    this->_page.append("</html>\r\n");
}

