
#ifndef RSA_UTILS_H
#define RSA_UTILS_H

#include <sys/stat.h>
#include <fstream>
#include <sstream>

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
        return s;
    }
}

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

inline bool existsFile(const std::string &filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

#endif //RSA_UTILS_H
