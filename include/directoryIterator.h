
#ifndef BUTTERFLY_DIRECTORYITERATOR_H
#define BUTTERFLY_DIRECTORYITERATOR_H

#include <boost/filesystem.hpp>

#include "logger.h"

namespace butterfly
{

/**
 * Class DirectoryIterator to iterate recursively through directories
 */
class DirectoryIterator
{

private:

public:

    /**
     * Constructor DirectoryIterator
     */
    DirectoryIterator();

    /**
     * Destructor DirectoryIterator
     */
    ~DirectoryIterator();

    /**
     * Checks if given file path is a directory
     *
     * @param path: const reference boost::filesystem::path&
     * @return boolean: true if path is a directory else false
     */
    bool isDirectory(const boost::filesystem::path &path);

    /**
     * Checks if given file path is a file
     *
     * @param path: const reference boost::filesystem::path&
     * @return boolean: true if path is a file else false
     */
    bool isFile(const boost::filesystem::path &path);

    /**
     * Get recursively all files from given path
     *
     * @param p: const reference filesystem path
     * @return std::vector including all file paths
     */
    std::vector<boost::filesystem::path> getAllFiles(const boost::filesystem::path &p);

    /**
     * Get recursively all directories from given path
     *
     * @param p: const reference filesystem path
     * @return std::vector<boost::filesystem::path> including all directory paths
     */
    std::vector<boost::filesystem::path> getAllDirectories(const boost::filesystem::path &p);

    /**
     * Get only files from given directory path
     *
     * @param p: filesytem path
     * @return std::vector including the file paths
     */
    std::vector<boost::filesystem::path> getFilesFromDir(const boost::filesystem::path &p);

    /**
    * Get the file size from given file path
    *
    * @param file: const boost::filesystem::path&
    * @return size of file in bytes
    */
    uintmax_t getFileSize(const boost::filesystem::path &file);
};

} // namespace butterfly

#endif //BUTTERFLY_DIRECTORYITERATOR_H
