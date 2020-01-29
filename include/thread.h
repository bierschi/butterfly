//
// Created on 27.01.20.
//

#ifndef RANSOMWARE_THREAD_H
#define RANSOMWARE_THREAD_H

#include <pthread.h>

/**
 * Base Class Thread to provide basic methods for handling thread execution
 */
class Thread {

private:
    pthread_t _self;

public:
    /**
     * Constructor
     *
     * Usage: new Thread()
     *
     */
    Thread();

    /**
     * Destructor
     */
    virtual ~Thread();

    /**
     * start method creates a new pthread object
     */
    void start();

    /**
     * joins the executed thread safely
     */
    void join();

    /**
     * detached the current thread from the caller thread
     */
    void detach();

protected:

    /**
     *  virtual execute method for subclasses
     */
    virtual void execute() = 0;

private:
    /**
     * static executorFunc method
     */
    static void *executorFunc(void *exec);

};


#endif //RANSOMWARE_THREAD_H
