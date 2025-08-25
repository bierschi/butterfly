
#ifndef BUTTERFLY_CRYPTOTHREAD_H
#define BUTTERFLY_CRYPTOTHREAD_H

#include <vector>
#include <string>

#include "threadWrapper.h"
#include "logger.h"


namespace butterfly
{

namespace hybrid
{

/**
* Class CryptoThread to create dedicated threads for the Encryption and Decryption phase
*/
class CryptoThread
{

private:
    std::vector<ThreadWrapper> _threads;

    /**
     * pure virtual method for the sub classes to implement
     *
     * @param filepath: path for the file
     */
    virtual void handleLargeFilesWithAES(const std::string &filepath) = 0;

public:

    /**
     * Constructor CryptoThread
     */
    CryptoThread();

    /**
     * Virtual Destructor CryptoThread
     */
    virtual ~CryptoThread();

    /**
     * Creates the thread with filepath as parameter
     *
     * @param filepath: path to the file
     */
    void create(const std::string &filepath);

    /**
     * Joins all previous created threads
     */
    void joinThreads();
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_CRYPTOTHREAD_H
