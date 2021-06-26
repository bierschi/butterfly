#ifndef BUTTERFLY_THREAD_H
#define BUTTERFLY_THREAD_H

#include <pthread.h>

/**
 * Base Class Thread to provide basic methods for handling thread execution
 */
class Thread
{

private:
    pthread_t _self;

public:

    /**
     * Thread Constructor
     */
    Thread();

    /**
     * Virtual Destructor
     */
    virtual ~Thread();

    /**
     * Start method creates a new pthread object
     */
    void start();

    /**
     * Joins the executed thread safely
     */
    void join();

    /**
     * Detach the current thread from the caller thread
     */
    void detach();

protected:

    /**
     *  Virtual execute method for subclasses
     */
    virtual void execute() = 0;

private:
    /**
     * Static executorFunc method
     */
    static void *executorFunc(void *exec);

};

#endif //BUTTERFLY_THREAD_H
