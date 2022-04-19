
#include "browser.h"

namespace butterfly
{

Browser::Browser(const std::string &terminalCMD) : _terminalCMD(terminalCMD), _running(false)
{

}

void Browser::run(const std::string &url)
{

    std::string result;
    while(_running)
    {
        std::string cmd = _terminalCMD + " " + url;
        butterfly::exec(cmd, result);

        if (result.find("not found") != std::string::npos)
        {
            // error case, throw exception
            //std::cout << "Error" << std::endl;
            _running = false;
        }
    }

}

void Browser::open(const std::string &url, bool blocking)
{
    if (blocking)
    {
        std::string result;
        std::string cmd = _terminalCMD + " " + url;
        butterfly::exec(cmd, result);
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
