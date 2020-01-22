//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_DIRECTORYITERATOR_H
#define RANSOMWARE_DIRECTORYITERATOR_H

#include <boost/filesystem.hpp>
#include <iostream>
/**
 *
 */
class DirectoryIterator {

private:
    std::string _start;

public:
    DirectoryIterator(std::string& start);
    ~DirectoryIterator();

private:
    bool isDirectory(const boost::filesystem::path& path);
    bool isFile(const boost::filesystem::path& path);
};


#endif //RANSOMWARE_DIRECTORYITERATOR_H
