
#include "baseThread.h"

namespace butterfly
{

BaseThread::BaseThread(bool start) : _running(false)
{
    LOG_INFO("Create Class BaseThread")

    if (start)
        this->start();

}

BaseThread::~BaseThread()
{
    _running = false;
    //_thread.join();
}

bool BaseThread::start()
{

    if (_running)
        return false;


    _running = true;
    _thread = std::thread(std::bind(&BaseThread::execution, this));

    return true;
}

bool BaseThread::stop()
{
    if (!_running)
        return false;

    _running = false;

    return true;
}

void BaseThread::execution()
{
    /*
    while (_running)
    {
        run();
    }*/

    this->run();
}

} // namespace butterfly
