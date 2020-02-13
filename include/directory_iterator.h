//
// Created on 22.01.20.
//

#ifndef RANSOMWARE_DIRECTORY_ITERATOR_H
#define RANSOMWARE_DIRECTORY_ITERATOR_H

#include <boost/filesystem.hpp>
#include <iostream>

/**
 * Class DirectoryIterator
 */
class DirectoryIiterator {

private:
    std::vector<boost::filesystem::path> _files;
    std::vector<boost::filesystem::path> _directories;

    /**
     * checks if given path is a directory
     *
     * @param path: const boost::filesystem::path&
     * @return bool true or false
     */
    bool isDirectory(const boost::filesystem::path& path);

    /**
     * checks if given path is a file
     *
     * @param path: const boost::filesystem::path&
     * @return bool true or false
     */
    bool isFile(const boost::filesystem::path& path);

public:
    /**
     * Default Constructor
     */
    DirectoryIiterator();

    /**
     * Destructor
     */
    ~DirectoryIiterator();

    /**
     * get recursively all files from given path
     *
     * @param f: const boost::filesystem::path&
     * @return std::vector<boost::filesystem::path>
     */
    std::vector<boost::filesystem::path> getFiles(const boost::filesystem::path& f);

    /**
     * get recursively all directories from given path
     *
     * @param f: const boost::filesystem::path&
     * @return std::vector<boost::filesystem::path>
     */
    std::vector<boost::filesystem::path> getDirectories(const boost::filesystem::path& f);

    /**
     * get only the files from given directory path
     *
     * @param dir: const boost::filesystem::path&
     * @return std::vector<boost::filesystem::path>
     */
    std::vector<boost::filesystem::path> getFilesFromDir(const boost::filesystem::path& dir);

    /**
     * get the file size from given file path
     *
     * @param file: const boost::filesystem::path&
     * @return uintmax_t
     */
    uintmax_t getFileSize(const boost::filesystem::path& file);

};


#endif //RANSOMWARE_DIRECTORY_ITERATOR_H
