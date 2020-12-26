
#include "directoryIterator.h"

namespace butterfly {

DirectoryIterator::DirectoryIterator() {

}

DirectoryIterator::~DirectoryIterator() {

}

bool DirectoryIterator::isFile(const boost::filesystem::path &path) {
    return boost::filesystem::is_regular_file(path);
}

bool DirectoryIterator::isDirectory(const boost::filesystem::path &path) {
    return boost::filesystem::is_directory(path);
}

std::vector<boost::filesystem::path> DirectoryIterator::getAllFiles(const boost::filesystem::path &f) {

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> files;

    if (boost::filesystem::is_directory(f)) {
        for (boost::filesystem::recursive_directory_iterator it{f, ec}, end; it != end; it.increment(ec)) {
            if (!boost::filesystem::is_directory(it->path())) {
                files.push_back(it->path());
            }
        }
    }
    else {
        files.push_back(f);
    }
    return files;
}

std::vector<boost::filesystem::path> DirectoryIterator::getFilesFromDir(const boost::filesystem::path &f) {

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> files;

    for (boost::filesystem::directory_iterator it(f, ec), end; it!= end; it.increment(ec)) {
        if (!boost::filesystem::is_directory(it->path())) {
            files.push_back(it->path());
        }
    }
    return files;
}

} // namespace butterfly
