
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
    joinThreads();
}

void CryptoThread::create(const std::string &filepath)
{
    _threads.emplace_back(&CryptoThread::handleLargeFilesWithAES, this, filepath);
}

void CryptoThread::joinThreads()
{

    for (ThreadWrapper &thread: _threads)
    {
        if ( thread.joinable() )
        {
            thread.join();
        }
    }
}

} // namespace hybrid

} //namespace butterfly
