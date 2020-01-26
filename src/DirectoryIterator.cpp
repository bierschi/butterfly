//
// Created on 22.01.20.
//

#include "DirectoryIterator.h"


DirectoryIterator::DirectoryIterator() {

}

DirectoryIterator::~DirectoryIterator() {

}

std::vector<boost::filesystem::path> DirectoryIterator::getFiles(const boost::filesystem::path& f) {

    boost::system::error_code ec;

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

std::vector<boost::filesystem::path> DirectoryIterator::getDirectories(const boost::filesystem::path &f) {

    boost::system::error_code ec;

    if (boost::filesystem::is_directory(f)) {
        for (boost::filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec)) {
            if (boost::filesystem::is_directory(it->path())) {
                _directories.push_back(it->path());
            }
        }
    }
    return _directories;
}

std::vector<boost::filesystem::path> DirectoryIterator::getFilesFromDir(const boost::filesystem::path &dir) {

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> filesFromDir;

    for (boost::filesystem::directory_iterator it(dir, ec), end; it!= end; it.increment(ec)) {
        if (!boost::filesystem::is_directory(it->path())) {
            filesFromDir.push_back(it->path());
        }
    }
    return filesFromDir;
}

bool DirectoryIterator::isDirectory(const boost::filesystem::path& path) {

    return boost::filesystem::is_directory(path);
}

bool DirectoryIterator::isFile(const boost::filesystem::path &path) {

    return boost::filesystem::is_regular_file(path);
}