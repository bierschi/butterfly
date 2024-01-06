
#ifndef BUTTERFLY_CRYPTOPROCESS_H
#define BUTTERFLY_CRYPTOPROCESS_H

#include <iostream>
#include <vector>
#include <sys/wait.h>
#include <unistd.h>

#include "logger.h"

namespace butterfly
{

namespace hybrid
{

/**
* Class CryptoProcess to create dedicated processes for the Encryption and Decryption phase
*/
class CryptoProcess
{

private:
    std::vector<pid_t> _processIds;

    /**
     * pure virtual method for the sub classes to implement
     *
     * @param filepath: path for the file
     */
    virtual void handleLargeFilesWithAES(const std::string& filepath) = 0;

public:

    /**
     * Constructor CryptoProcess
     */
    CryptoProcess();

    /**
     * Virtual Destructor CryptoProcess
     */
    virtual ~CryptoProcess();

    /**
     * Creates the process with filepath as parameter
     *
     * @param filepath: path to the file
     */
    void create(const std::string &filepath);

    /**
     * Waits for all previous created processes
     */
    void waitAll();
};

} // namespace hybrid

} // namespace butterfly

#endif //BUTTERFLY_CRYPTOPROCESS_H
