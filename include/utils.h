
#ifndef BUTTERFLY_UTILS_H
#define BUTTERFLY_UTILS_H

#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <iomanip>

namespace butterfly
{

/**
 * Get file size from given filepath
 *
 * @param filepath: filepath as const std::string reference
 * @param MBytes: return the value in MBytes
 * @return size of file in bytes
 */
inline double getFileSize(const std::string &filepath, bool MBytes=true)
{
    struct stat stat_buf;

    int rc = stat(filepath.c_str(), &stat_buf);

    if (rc != 0)
    {
        return -1;
    } else {

        if (MBytes)
        {
            return (static_cast<double>(stat_buf.st_size) / 1000000.0);
        }
        return static_cast<double>(stat_buf.st_size);
    }

}

/**
 * Read a binary file
 *
 * @param filepath: path to the file
 * @return content as std::string
 */
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

/**
 * Write to a binary file
 *
 * @param filepath: path to the file
 * @param content: content to write to file
 * @param contentLength: length of the content
 * @param append: Appends the content to the file
 * @return True if writing was successful
 */
inline bool writeBinFile(const std::string &filepath, const char* content, long contentLength, bool append=false)
{
    std::fstream out;
    if (append)
    {
        out.open(filepath, std::ios::out | std::ios::app | std::ios::binary);
    } else
    {
        out.open(filepath, std::ios::out | std::ios::binary);
    }

    if (out.is_open())
    {
        out.write(content, contentLength);
        return true;
    } else
    {
        return false;
    }
}

/**
 * Remove file from given filepath
 *
 * @param filepath: path to the file
 * @return True if removing was succesful
 */
inline bool removeFile(const std::string &filepath)
{

    int rc = std::remove(filepath.c_str());

    if (rc == 0)
    {
        return true;
    } else
    {
        return false;
    }

}

/**
 * Checks if an file exists or not
 *
 * @param filename: name of the file
 * @return True if file exits else false
 */
inline bool existsFile(const std::string& filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

inline std::string string_to_hex(const std::string& in) {
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

inline std::string hex_to_string(const std::string& in) {
    std::string output;

    if ((in.length() % 2) != 0) {
        throw std::runtime_error("String is not valid length ...");
    }

    size_t cnt = in.length() / 2;

    for (size_t i = 0; cnt > i; ++i) {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;

        output.push_back(static_cast<char>(static_cast<unsigned char>(s)));
    }

    return output;
}

} // namespace butterfly

#endif //BUTTERFLY_UTILS_H
