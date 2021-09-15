
#include "directoryIterator.h"

namespace butterfly
{

DirectoryIterator::DirectoryIterator()
{

}

bool DirectoryIterator::isFile(const boost::filesystem::path &path)
{
    return boost::filesystem::is_regular_file(path);
}

bool DirectoryIterator::isDirectory(const boost::filesystem::path &p)
{
    return boost::filesystem::is_directory(p);
}

std::vector<boost::filesystem::path> DirectoryIterator::getAllFiles(const boost::filesystem::path &p)
{

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> files;

    if (boost::filesystem::is_directory(p))
    {
        for (boost::filesystem::recursive_directory_iterator it{p, ec}, end; it != end; it.increment(ec))
        {
            if (!boost::filesystem::is_directory(it->path()))
            {
                files.push_back(it->path());
            }
        }
    } else
    {
        files.push_back(p);
    }

    return files;
}

std::vector<boost::filesystem::path> DirectoryIterator::getAllDirectories(const boost::filesystem::path &p)
{

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> directories;

    if (boost::filesystem::is_directory(p))
    {
        for (boost::filesystem::recursive_directory_iterator it{p, ec}, end; it != end; it.increment(ec))
        {
            if (boost::filesystem::is_directory(it->path()))
            {
                directories.push_back(it->path());
            }
        }
    }
    return directories;
}

std::vector<boost::filesystem::path> DirectoryIterator::getFilesFromDir(const boost::filesystem::path &p)
{

    boost::system::error_code ec;
    std::vector<boost::filesystem::path> files;

    for (boost::filesystem::directory_iterator it(p, ec), end; it != end; it.increment(ec))
    {
        if (!boost::filesystem::is_directory(it->path()))
        {
            files.push_back(it->path());
        }
    }
    return files;
}

uintmax_t DirectoryIterator::getFileSize(const boost::filesystem::path &file)
{

    if (isFile(file))
    {
        return boost::filesystem::file_size(file);
    } else
    {
        LOG_ERROR("Not a regular File: " << file);
        return 0;
    }

}

std::string DirectoryIterator::getFileExtension(const boost::filesystem::path &p)
{
    return p.extension().string();
}

} // namespace butterfly
