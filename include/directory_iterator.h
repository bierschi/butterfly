//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_DIRECTORY_ITERATOR_H
#define RANSOMWARE_DIRECTORY_ITERATOR_H

#include <boost/filesystem.hpp>
#include <iostream>

/**
 *
 */
class DirectoryIiterator {

private:
    std::vector<boost::filesystem::path> _files;
    std::vector<boost::filesystem::path> _directories;

public:
    DirectoryIiterator();
    ~DirectoryIiterator();

    std::vector<boost::filesystem::path> getFiles(const boost::filesystem::path& f);
    std::vector<boost::filesystem::path> getDirectories(const boost::filesystem::path& f);

    std::vector<boost::filesystem::path> getFilesFromDir(const boost::filesystem::path& dir);
    uintmax_t getFileSize(const boost::filesystem::path& file);

private:
    bool isDirectory(const boost::filesystem::path& path);
    bool isFile(const boost::filesystem::path& path);
};


#endif //RANSOMWARE_DIRECTORY_ITERATOR_H
