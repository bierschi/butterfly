#include "connManager.h"

namespace butterfly
{

ConnManager::ConnManager(const std::string &queryHostname, int queryPort, unsigned int queryTime) : _running(false), _queryHostname(queryHostname), _queryPort(queryPort), _queryTime(queryTime), _tcpSocket(new TCPSocket())
{

}

ConnManager::~ConnManager()
{

}

void ConnManager::registerConnStateChangeCB(std::function<void(bool)>)
{

}

bool ConnManager::isInternetAvailable()
{
    return true;
}

void ConnManager::start()
{

}

void ConnManager::stop()
{

}

}  // namespace butterfly
