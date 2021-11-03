
#include "connManager.h"

namespace butterfly
{

ConnManager::ConnManager(const std::string &queryHostname, int queryPort, unsigned int queryTime) : _running(false), _queryHostname(queryHostname), _queryPort(queryPort), _queryTime(queryTime), _tcpSocket(new TCPSocket())
{

}

ConnManager::~ConnManager()
{
    stop();
}

void ConnManager::run()
{
    bool oldState = false, newState = false;
    while(_running)
    {
        newState = isInternetAvailable();

        if (oldState != newState)
        {
            if (_connStateChangeCB)
            {
                _connStateChangeCB(true);
            }
        }
        oldState = newState;

        sleep(_queryTime);
    }
}

void ConnManager::registerConnStateChangeCB(std::function<void(bool)> cb)
{
    _connStateChangeCB = cb;
}

bool ConnManager::isInternetAvailable()
{

    _tcpSocket = std::unique_ptr<TCPSocket>(new TCPSocket());

    return _tcpSocket->connect(_queryHostname, _queryPort);
}

void ConnManager::start()
{
    _running = true;
    _thread = std::thread(&ConnManager::run, this);
    _thread.detach();
}

void ConnManager::stop()
{
    _running = false;
}

} // namespace butterfly
