
#include "crypto/cryptoProcess.h"

namespace butterfly
{

namespace hybrid
{

CryptoProcess::CryptoProcess()
{
    #ifdef LOGGING
    LOG_TRACE("Create class CryptoProcess");
    #endif
}

CryptoProcess::~CryptoProcess()
{
    for (pid_t pid : _processIds)
    {
        waitpid(pid, nullptr, 0);
    }
}

void CryptoProcess::create(const std::string &filepath)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        #ifdef LOGGING
        LOG_ERROR("Error on creating new Process for file " + filepath);
        #else
        std::cerr << "Error on creating new Process for file " + filepath << std::endl;
        #endif
        return;
    }

    if (pid == 0)
    {
        handleLargeFilesWithAES(filepath);
        _exit(EXIT_SUCCESS);
    } else
    {
        _processIds.push_back(pid);
    }
}

void CryptoProcess::waitAll()
{
    for (pid_t pid : _processIds)
    {
        waitpid(pid, nullptr, 0);
    }
}

} // namespace hybrid

} // namespace butterfly