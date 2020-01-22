//
// Created on 22.01.20.
//

#include "DirectoryIterator.h"


DirectoryIterator::DirectoryIterator(std::string&  start) : _start(start){

    boost::filesystem::directory_iterator end;

    for (boost::filesystem::directory_iterator it(_start); it != end; it++) {
        std::cout << *it << std::endl;
        if (isDirectory(it->path())) {
            std::cout << "Dir: " << it->path() << std::endl;
        } else if (isFile(it->path())) {
            std::cout << "File: " << it->path() << std::endl;
        }
        //std::cout << isDirectory(it->path()) << std::endl;
    }

}

DirectoryIterator::~DirectoryIterator() {

}

bool DirectoryIterator::isDirectory(const boost::filesystem::path& path) {

    return boost::filesystem::is_directory(path);
}

bool DirectoryIterator::isFile(const boost::filesystem::path &path) {

    return boost::filesystem::is_regular_file(path);
}