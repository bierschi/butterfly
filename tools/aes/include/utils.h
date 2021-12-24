
#ifndef AES_UTILS_H
#define AES_UTILS_H

#include <fstream>
#include <sstream>
#include <iomanip>

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

inline bool appendFileExtension(const std::string &filename, const std::string &extension)
{
    std::string outFile = filename + extension;
    if ( std::rename(filename.c_str(), outFile.c_str()) == 0 )
    {
        return true;
    } else
    {
        return false;
    }
}

inline bool removeFileExtension(std::string &filename, const std::string &extension)
{
    if ( filename.find(extension) != std::string::npos )
    {
        std::string old = filename;
        filename.erase(filename.length() - extension.length());

        if ( std::rename(old.c_str(), filename.c_str()) == 0 )
        {
            return true;
        } else
        {
            return false;
        }

    } else
    {
        return false;
    }
}

inline std::string string2Hex(const std::string &in)
{
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

inline std::string hex2String(const std::string &in)
{
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

#endif //AES_UTILS_H
