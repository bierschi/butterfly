
#ifndef BUTTERFLY_UTILS_H
#define BUTTERFLY_UTILS_H

#include <sys/stat.h>

namespace butterfly
{

/**
 * Get file size from given filepath
 *
 * @param filepath: filepath as const std::string reference
 * @return size of file in bytes
 */
long getFileSize(const std::string &filepath)
{
    struct stat stat_buf;

    int rc = stat(filepath.c_str(), &stat_buf);

    return rc == 0 ? stat_buf.st_size : -1;
}

} // namespace butterfly

#endif //BUTTERFLY_UTILS_H
