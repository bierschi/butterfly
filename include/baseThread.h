#ifndef BUTTERFLY_BASETHREAD_H
#define BUTTERFLY_BASETHREAD_H

#include <thread>

#include "logger.h"

namespace butterfly
{

/**
 * Base Class Thread to provide basic methods for handling thread execution
 */
class BaseThread
{

private:
    std::thread _thread;
    bool _running;

protected:
    /**
     * Execution thread in base class
     */
    void execution();

public:

    /**
     * Abstract run method for subclasses
     */
    virtual void run() = 0;

    /**
     *
     * @param start
     */
    explicit BaseThread(bool start = false);

    /**
     * Destructor BaseThread
     */
    virtual ~BaseThread();

    /**
     * Start method for the thread execution
     *
     * @return True if start was successful
     */
    bool start();

    /**
     * Stop method for the thread execution
     *
     * @return True if stop was successful
     */
    bool stop();

};

} // namespace butterfly

#endif //BUTTERFLY_BASETHREAD_H
