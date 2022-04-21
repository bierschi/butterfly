
#ifndef BUTTERFLY_BROWSER_H
#define BUTTERFLY_BROWSER_H

#include <string>
#include <thread>
#include <atomic>

#include "bflyUtils.h"
#include "bflyExceptions.h"
#include "logger.h"

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
     * @param cmd
     */
    static void execute(const std::string &cmd);

    /**
     *
     * @param url
     */
    void run(const std::string &url);

public:

    /**
     * Constructor Browser
     *
     * Usage:
     *      std::shared_ptr<butterfly::Browser> browser = std::make_shared<butterfly::Browser>("x-www-browser");
     *      browser->open();
     *
     * @param terminalCMD: terminal command to open the browser
     */
    explicit Browser(const std::string &terminalCMD="x-www-browser");

    /**
     * Destructor Browser
     */
    ~Browser() = default;

    /**
     * Open the browser with URL
     *
     * @param url: URL to open
     * @param blocking: blocking mode
     */
    void open(const std::string &url, bool blocking=false);

    /**
     * Close the browser
     */
    void close();
};

} // namespace butterfly

#endif //BUTTERFLY_BROWSER_H
