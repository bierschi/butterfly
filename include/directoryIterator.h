
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
    ~DirectoryIterator() = default;

    /**
     * Checks if given file path is a directory
     *
     * @param p: const reference boost::filesystem::path&
     * @return boolean: true if path is a directory else false
     */
    static bool isDirectory(const boost::filesystem::path &p);

    /**
     * Checks if given file path is a file
     *
     * @param p: const reference boost::filesystem::path&
     * @return boolean: true if path is a file else false
     */
    static bool isFile(const boost::filesystem::path &p);

    /**
     * Get recursively all files from given path
     *
     * @param p: const reference filesystem path
     * @return std::vector including all file paths
     */
    static std::vector<boost::filesystem::path> getAllFiles(const boost::filesystem::path &p);

    /**
     * Get recursively all directories from given path
     *
     * @param p: const reference filesystem path
     * @return std::vector<boost::filesystem::path> including all directory paths
     */
    static std::vector<boost::filesystem::path> getAllDirectories(const boost::filesystem::path &p);

    /**
     * Get only files from given directory path
     *
     * @param p: filesytem path
     * @return std::vector including the file paths
     */
    static std::vector<boost::filesystem::path> getFilesFromDir(const boost::filesystem::path &p);

    /**
    * Get the file size from given file path
    *
    * @param file: const boost::filesystem::path&
    * @return size of file in bytes
    */
    static uintmax_t getFileSize(const boost::filesystem::path &file);

    /**
     * Get the file extension from given path
     *
     * @param p: const boost::filesystem::path&
     * @return file extension as std::string
     */
    static std::string getFileExtension(const boost::filesystem::path &p);
};

} // namespace butterfly

#endif //BUTTERFLY_DIRECTORYITERATOR_H
