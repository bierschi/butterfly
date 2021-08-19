
#ifndef BUTTERFLY_UTILS_H
#define BUTTERFLY_UTILS_H

#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <vector>

namespace butterfly
{

/**
 * Get file size from given filepath
 *
 * @param filepath: filepath as const std::string reference
 * @return size of file in bytes
 */
inline long getFileSize(const std::string &filepath)
{
    struct stat stat_buf;

    int rc = stat(filepath.c_str(), &stat_buf);

    return rc == 0 ? stat_buf.st_size : -1;
}

inline std::string readBinFile(const std::string &filepath)
{
    std::ifstream in(filepath, std::ios::in | std::ios::binary);
    std::string s;

    if (in.is_open())
    {
        std::stringstream strStream;
        strStream << in.rdbuf();
        s = strStream.str();
        return s;
    } else
    {
        LOG_ERROR("Failed to open file " << filepath);
        return s;
    }
}

inline void writeBinFile(const std::string &filename, const char* content, long fileLength)
{

    std::fstream out(filename, std::ios::out | std::ios::binary);
    if (out.is_open())
    {
        out.write(content, fileLength);
    } else
    {
        LOG_ERROR("Failed to open file " << filename);
    }
}

} // namespace butterfly

#endif //BUTTERFLY_UTILS_H
