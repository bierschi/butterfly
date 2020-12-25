//
// Created on 22.01.20.
//

#include "../include/directory_iterator.h"


DirectoryIiterator::DirectoryIiterator() : _directories({}), _files({}){

}

DirectoryIiterator::~DirectoryIiterator() {

}

std::vector<boost::filesystem::path> DirectoryIiterator::getFiles(const boost::filesystem::path& f) {

    boost::system::error_code ec;
    _files.clear();

    if (boost::filesystem::is_directory(f)) {
        for (boost::filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec)) {
            if (!boost::filesystem::is_directory(it->path())) {
                _files.push_back(it->path());
            }
        }
    }
    else {
        _files.push_back(f);
    }

    return _files;
}

std::vector<boost::filesystem::path> DirectoryIiterator::getDirectories(const boost::filesystem::path &f) {

    boost::system::error_code ec;
    _directories.clear();

    if (boost::filesystem::is_directory(f)) {
        for (boost::filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec)) {
            if (boost::filesystem::is_directory(it->path())) {
                _directories.push_back(it->path());
            }
        }
    }
    return _directories;
}

std::vector<boost::filesystem::path> DirectoryIiterator::getFilesFromDir(const boost::filesystem::path &dir) {

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> filesFromDir;

    for (boost::filesystem::directory_iterator it(dir, ec), end; it!= end; it.increment(ec)) {
        if (!boost::filesystem::is_directory(it->path())) {
            filesFromDir.push_back(it->path());
        }
    }
    return filesFromDir;
}

uintmax_t DirectoryIiterator::getFileSize(const boost::filesystem::path &file) {
    if (isFile(file)) {
        return boost::filesystem::file_size(file);
    } else {
        std::cout << "Not a regular file: " << file << std::endl;
    }
}

bool DirectoryIiterator::isDirectory(const boost::filesystem::path& path) {

    return boost::filesystem::is_directory(path);
}

bool DirectoryIiterator::isFile(const boost::filesystem::path &path) {

    return boost::filesystem::is_regular_file(path);
}