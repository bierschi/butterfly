
#include "baseThread.h"

namespace butterfly
{

BaseThread::BaseThread(bool ) : _running(false)
{
    LOG_INFO("Create Class BaseThread")

    //if (start)
    //    this->start();

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
    _thread = std::thread(&BaseThread::execution, this);

    return true;
}

bool BaseThread::stop()
{
    if (!_running)
        return false;

    _running = false;

    return true;
}

void BaseThread::join()
{
    if (_thread.joinable())
        _thread.join();
}

void BaseThread::execution(void *t)
{
    /*
    while (_running)
    {
        run();
    }*/

    static_cast<BaseThread*>(t)->run();
}

} // namespace butterfly
