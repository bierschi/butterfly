
#ifndef BUTTERFLY_DIRECTORYITERATOR_H
#define BUTTERFLY_DIRECTORYITERATOR_H

#include <boost/filesystem.hpp>

namespace butterfly {

class DirectoryIterator {

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
     *
     * @param f
     * @return
     */
    std::vector<boost::filesystem::path> getAllFiles(const boost::filesystem::path &f);

    /**
     *
     * @param f
     * @return
     */
    std::vector<boost::filesystem::path> getFilesFromDir(const boost::filesystem::path &f);
};

} // namespace butterfly
#endif //BUTTERFLY_DIRECTORYITERATOR_H
