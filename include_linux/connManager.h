
#ifndef BUTTERFLY_CONNMANAGER_H
#define BUTTERFLY_CONNMANAGER_H

#include <functional>

#include "tcpSocket.h"
#include "threadWrapper.h"

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
    ThreadWrapper _thread;
    std::function<void(bool)> _connStateChangeCB;
    std::unique_ptr<TCPSocket> _tcpSocket;

    /**
    * Run method which is invoked by the thread execution
    */
    void run();

public:

    /**
     * Constructor ConnManager
     *
     * Usage:
     *      std::shared_ptr<butterfly::ConnManager> _connMan = std::make_shared<butterfly::ConnManager>();
     *      _connMan->start();
     *      _connMan->isInternetAvailable();

     * @param queryHostname: Hostname for the query
     * @param queryPort: Port for the query
     * @param queryTime: Time interval for the next query
     */
    explicit ConnManager(const std::string &queryHostname="google.com", int queryPort=80, unsigned int queryTime=10);

    /**
     * Destructor ConnManager
     */
    ~ConnManager();

    /**
     * Registers the connection state change callback
     *
     * @param cb: callback function
     */
    void registerConnStateChangeCB(std::function<void(bool)> cb);

    /**
     * Method to check if internet is available
     *
     * @return True if internet connection is available, else False
     */
    bool isInternetAvailable();

    /**
     * Method to start the periodic thread
     */
    void start();

    /**
     * Method to stop the periodic thread
     */
    void stop();
};

} // namespace butterfly

#endif //BUTTERFLY_CONNMANAGER_H
