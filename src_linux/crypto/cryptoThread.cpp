
#include "crypto/cryptoThread.h"

namespace butterfly
{

namespace hybrid
{

CryptoThread::CryptoThread()
{
    #ifdef LOGGING
    LOG_TRACE("Create class CryptoThread");
    #endif
}

CryptoThread::~CryptoThread()
{
    for (std::thread &thread : _threads)
    {
        if ( thread.joinable() )
        {
            thread.join();
        }
    }
}

void CryptoThread::create(const std::string &filepath)
{
    _threads.emplace_back(&CryptoThread::handleLargeFilesWithAES, this, filepath);
}

void CryptoThread::joinThreads()
{
    for (std::thread &thread : _threads)
    {
        if ( thread.joinable() )
        {
            thread.join();
        }
    }
}

} // namespace hybrid

} //namespace butterfly
