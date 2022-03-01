#include <iostream>
#include <iomanip>


int main()
{
    char buffer[1024];
    memcpy(buffer, "hkdj\0hsad ajksh kjsadkjh dajksh k\0h dakjhdsajh djahs \0", 53);
    std::string copy(buffer, 54);
    std::cout << std::setw(25) << "buffer: " << buffer << "|" << std::endl;
    std::cout << std::setw(25) << "copy: " << copy << "|" << std::endl;
    std::string copy_copy(copy);
    std::cout << std::setw(25) << "copy_copy: " << copy_copy << "|" << std::endl;
    copy_copy.resize(45);
    std::cout << std::setw(25) << "copy_copy: " << copy_copy << "|" << std::endl;
    std::cout << std::setw(25) << "copy_copy iterators: ";
    for (std::string::iterator it = copy.begin(); it != copy.end(); it++)
        std::cout << (*it);
    std::cout << "|" << std::endl;

    std::string sub = copy.substr(0, 23);
    std::cout << std::setw(25) << "copy: " << copy << "|" << std::endl;
    std::cout << std::setw(25) << "sub: " << sub << "|" << std::endl;
    std::string concat = copy;
    concat += copy;
    std::cout << std::setw(25) << "concat: " << concat << "|" << std::endl;
    std::cout << std::setw(25) << "concat.c_str(): ";
    std::cout.write(concat.c_str(), concat.length());
    std::cout << "|" << std::endl;
    std::string &reference = copy;
    std::string ref_copy = reference;
    ref_copy.resize(25);
    std::cout << std::setw(25) << "copy: " << copy << "|" << std::endl;
    std::cout << std::setw(25) << "reference: " << reference << "|" << std::endl;
    std::cout << std::setw(25) << "reference copy: " << ref_copy << "|" << std::endl;
    return (0);
}