
#ifndef BUTTERFLY_BROWSER_H
#define BUTTERFLY_BROWSER_H

#include <string>
#include <thread>
#include <atomic>

#include "bflyUtils.h"

namespace butterfly
{

/**
 * Class Browser to open and close a webpage
 */
class Browser
{

private:
    std::string _terminalCMD;
    std::atomic<bool> _running;
    std::thread _browserThread;

    /**
     *
     * @param url
     */
    void run(const std::string &url);

public:

    /**
     *
     * @param terminalCMD
     */
    explicit Browser(const std::string &terminalCMD="x-www-browser");

    /**
     *
     */
    ~Browser() = default;

    /**
     *
     * @param url
     */
    void open(const std::string &url, bool blocking=false);

    /**
     *
     */
    void close();
};

} // namespace butterfly

#endif //BUTTERFLY_BROWSER_H
