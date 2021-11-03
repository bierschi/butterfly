
#ifndef BUTTERFLY_CONNMANAGER_H
#define BUTTERFLY_CONNMANAGER_H

#include <thread>
#include <functional>

#include "tcpSocket.h"

namespace butterfly
{

/**
 * Class ConnManager to manage the connection state
 */
class ConnManager
{

private:
    bool _running;
    std::string _queryHostname;
    int _queryPort;
    unsigned int _queryTime;
    std::unique_ptr<TCPSocket> _tcpSocket;
    std::thread _thread;
    std::function<void(bool)> _connStateChangeCB;

    /**
    * Run method which is invoked by the thread execution
    */
    void run();

public:

    /**
     * Constructor ConnManager
     *
     * @param queryHostname
     * @param queryPort
     * @param queryTime
     */
    explicit ConnManager(const std::string &queryHostname="google.com", int queryPort=80, unsigned int queryTime=5);

    /**
     * Destructor ConnManager
     */
    virtual ~ConnManager();

    /**
     *
     * @param cb
     */
    void registerConnStateChangeCB(std::function<void(bool)> cb);

    /**
     *
     * @return
     */
    bool isInternetAvailable();

    /**
     *
     */
    void start();

    /**
     *
     */
    void stop();
};

} // namespace butterfly

#endif //BUTTERFLY_CONNMANAGER_H
