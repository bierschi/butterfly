
#ifndef BUTTERFLY_BFLYUTILS_H
#define BUTTERFLY_BFLYUTILS_H

#include <sys/stat.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdio>
#include <iomanip>

namespace tools
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
 * @return True if removing was successful
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
 * Appends the extension to the filename
 *
 * @param filename: name of the file
 * @param extension: extension to add
 * @return True if appending of extension was successful
 */
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

/**
 * Removes the extension from the filename
 *
 * @param filename: name of the file
 * @param extension: extension to remove
 * @return True if removing of extension was successful
 */
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

/**
 * Checks if an file exists or not
 *
 * @param filename: name of the file
 * @return True if file exits else false
 */
inline bool existsFile(const std::string &filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

/**
 * Converts string to HEX
 *
 * @param in: std::string
 * @return hex string
 */
inline std::string string2Hex(const std::string &in)
{
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i)
    {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

/**
 * Converts HEX to String
 *
 * @param in: HEX string
 * @return std::string
 */
inline std::string hex2String(const std::string &in)
{
    std::string output;

    if ((in.length() % 2) != 0)
    {
        throw std::runtime_error("String is not valid length ...");
    }

    size_t cnt = in.length() / 2;

    for (size_t i = 0; cnt > i; ++i)
    {
        uint32_t s = 0;
        std::stringstream ss;
        ss << std::hex << in.substr(i * 2, 2);
        ss >> s;

        output.push_back(static_cast<char>(static_cast<unsigned char>(s)));
    }

    return output;
}

/**
 * Get Domain name from provided URL
 *
 * @param url: URL address
 * @return domain as std::string
 */
inline std::string getDomainFromUrl(std::string url)
{
    std::string http = "http://";
    size_t pos1 = url.find(http);
    if (pos1 != std::string::npos)
    {
        url.erase(pos1, http.length());
    }
    std::string https = "https://";
    size_t pos2 = url.find(https);

    if (pos2 != std::string::npos)
    {
        url.erase(pos2, https.length());
    }

    size_t pos3 = url.find('/');
    if (pos3 != std::string::npos)
    {
        url.erase(pos3, url.length());
    }

    size_t pos4 = url.find(':');
    if (pos4 != std::string::npos)
    {
        url.erase(pos4, url.length());
    }

    return url;
}

/**
* Get Route name from provided URL
*
* @param url: URL address
* @return domain as std::string
*/
inline std::string getRouteFromUrl(std::string url)
{
    std::string http = "http://";
    size_t pos1 = url.find(http);
    if (pos1 != std::string::npos)
    {
        url.erase(pos1, http.length());
    }
    std::string https = "https://";
    size_t pos2 = url.find(https);

    if (pos2 != std::string::npos)
    {
        url.erase(pos2, https.length());
    }

    size_t pos3 = url.find('/');
    if (pos3 != std::string::npos)
    {
        url.erase(0, pos3);
    } else
    {
        // not route was included
        url = "/";
    }

    return url;
}

/**
 * Creates a form param string with the content of the vector
 *
 * @param formParamVec: Vector of form parameters
 * @return form parameter string
 */
inline std::string createFormParamStr(std::vector<std::pair<std::string, std::string>> &formParamVec)
{
    std::string formParamStr;

    for(auto &it: formParamVec)
    {
        if( !formParamStr.empty() )
        {
            formParamStr.append("&");
        }
        formParamStr.append(it.first);
        formParamStr.append("=");
        formParamStr.append(it.second);

    }

    return formParamStr;
}

/**
 * Executes a command
 *
 * @param cmd: command to execute
 * @param result: result of the execution
 * @return boolean
 */
inline bool exec(const std::string &cmd, std::string &result)
{

    char buffer[128];
    std::string cmdWithRedirect = cmd + " 2>&1";
    FILE* pipe = popen(cmdWithRedirect.c_str(), "r");

    if ( !pipe )
    {
        pclose(pipe);
        return false;
    }

    while (fgets(buffer, sizeof buffer, pipe) != nullptr)
    {
        result += buffer;
    }
    pclose(pipe);

    return true;
}

} // namespace tools

#endif //BUTTERFLY_BFLYUTILS_H
