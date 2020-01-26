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
    std::vector<boost::filesystem::path> _files;
    std::vector<boost::filesystem::path> _directories;

public:
    DirectoryIterator();
    ~DirectoryIterator();

    std::vector<boost::filesystem::path> getFiles(const boost::filesystem::path& f);
    std::vector<boost::filesystem::path> getDirectories(const boost::filesystem::path& f);

    std::vector<boost::filesystem::path> getFilesFromDir(const boost::filesystem::path& dir);

private:
    bool isDirectory(const boost::filesystem::path& path);
    bool isFile(const boost::filesystem::path& path);
};


#endif //RANSOMWARE_DIRECTORYITERATOR_H
