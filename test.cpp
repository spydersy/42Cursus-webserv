/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelarif <abelarif@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/03 17:11:28 by abelarif          #+#    #+#             */
/*   Updated: 2022/03/04 23:17:57 by abelarif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <iostream>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>
#include <iomanip>

std::string getFileDate(std::string file) {
    struct stat t_stat;

    stat(file.c_str(), &t_stat);
    struct tm * timeinfo = localtime(&t_stat.st_ctime);
    std::string date = asctime(timeinfo);
    if (date.length() != 0) {
        date.erase(date.begin() + date.length() - 1);
    }
    return date;
}

std::string getFilePermissions(std::string file) {
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

#include<iostream>
#include<fstream>
int     getFileSize(std::string file) {
    

   std::ifstream in_file(file.c_str(), std::ios::binary);
   in_file.seekg(0, std::ios::end);
   int file_size = in_file.tellg();
//    std::cout<<"Size of the file is"<<" "<< file_size <<" "<<"bytes";
    return (file_size);
}


// #include <fstream>
// #include <iostream>
// std::ifstream::pos_type filesize(const char* filename)
// {
//     std::ifstream in(filename, std::ifstream::ate | std::ifstream::binary);
//     return in.tellg(); 
// }

int main(int argc, char *argv[])
{

    DIR                 *d;
    struct dirent       *dir;
    std::string         path(argv[1]);
    
    std::string         autoIndexPage;
    
    autoIndexPage.append("<html>\r\n");
    autoIndexPage.append(" <style>\r\n");
    autoIndexPage.append(" th {\r\n");
    autoIndexPage.append("     text-align: left;\r\n");
    autoIndexPage.append(" }\r\n");
    autoIndexPage.append(" </style>\r\n");
    autoIndexPage.append("<head><title>Index of " + path + "</title></head>\r\n");
    autoIndexPage.append("<body>\r\n");
    autoIndexPage.append("<h1>Index of " + path + "</h1><hr><pre>\r\n");
    autoIndexPage.append("<table style=\"width:100%\">\r\n");
    autoIndexPage.append("<tr>\r\n");
    autoIndexPage.append("<th>Name</th>\r\n");
    autoIndexPage.append("<th>Size</th>\r\n");
    autoIndexPage.append("<th>Date</th>\r\n");
    autoIndexPage.append("</tr>\r\n");
    d = opendir(path.c_str());
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            // std::string content("<li><a href=\"" + path + dir->d_name + "\">" + std::string(dir->d_name) + "</a> " + getFileDate(path + "/" + dir->d_name) + " " + std::to_string(getFileSize(path + "/" + dir->d_name)) "</li>\r\n");
            // autoIndexPage.append(content);

            autoIndexPage.append("<tr>\r\n");
            autoIndexPage.append("<td><a href=\"" + path + dir->d_name + "\">" + dir->d_name + "</a></td>\r\n");
            autoIndexPage.append("<td>" + std::to_string(getFileSize(path + "/" + dir->d_name)) + "</td>\r\n");
            autoIndexPage.append("<td>" + getFileDate(path + "/" + dir->d_name) +"</td>");
            autoIndexPage.append("</tr>");

            // std::cout << "[" << dir->d_name << "|" << getFileDate(path + "/" + dir->d_name) << "|" << getFileSize(path + "/" + dir->d_name) << "]" << std::endl;
        }
        closedir(d);
    }
    autoIndexPage.append("</pre><hr></body>\r\n");
    autoIndexPage.append("</html>\r\n");
    std::cerr << autoIndexPage;
    return(0);
}

/*

// Autoindex template :
    <html>
    <head><title>Index of /autoindex/</title></head>
    <body>
    <h1>Index of /autoindex/</h1><hr><pre><a href="../">../</a>
    <a href="bifang/">bifang/</a> 31-May-2021 10:55 -
    <a href="cppjieba/">cppjieba/</a> 31-May-2021 09:45 -
    <a href="doxygen/">doxygen/</a> 27-May-2021 16:34 -
    <a href="gude/">gude/</a> 08-Jun-2021 20:17 -
    <a href="sql_insert/">sql_insert/</a> 08-Jun-2021 20:17 -
    </pre><hr></body>
    </html>
*/