
#include "browser.h"

namespace butterfly
{

Browser::Browser(const std::string &terminalCMD) : _terminalCMD(terminalCMD), _running(false)
{
    #ifdef LOGGING
    LOG_TRACE("Create class Browser");
    #endif
}

void Browser::execute(const std::string &cmd)
{
    std::string result;
    bool rc = butterfly::exec(cmd, result);

    if ( (result.find("not found") != std::string::npos) || (rc == false) )
    {
        throw BrowserException("Error at executing command " + cmd);
    }
}

void Browser::run(const std::string &url)
{

    std::string result;
    while(_running)
    {
        try
        {
            std::string cmd = _terminalCMD + " " + url;
            execute(cmd);
        } catch ( BrowserException &e )
        {
            _running = false;
            LOG_ERROR(e.getType() + ": " + e.what());
        }

    }

}

void Browser::open(const std::string &url, bool blocking)
{
    if (blocking)
    {
        std::string result;
        std::string cmd = _terminalCMD + " " + url;
        execute(cmd);

    } else
    {
        if ( !_running )
        {
            _running = true;
        }

        _browserThread = std::thread(&Browser::run, this, url);
    }

}

void Browser::close()
{

    if ( _running )
    {
        _running = false;
    }
}

} // namespace butterfly
