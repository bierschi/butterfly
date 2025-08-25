
#ifndef BUTTERFLY_THREADWRAPPER_H
#define BUTTERFLY_THREADWRAPPER_H

#include <iostream>
#include <thread>

namespace butterfly
{

/**
* class ThreadWrapper to wrap std::thread in a dedicated class
*/
class ThreadWrapper
{

private:
    std::thread m_thread;

public:

    /**
     * Template method for ThreadWrapper
     *
     * @tparam Function: Function for the thread
     * @tparam Args: Arguments for the thread
     * @param f: Function for the thread
     * @param args: Arguments for the thread
     */
    template<typename Function, typename... Args>
    explicit ThreadWrapper(Function &&f, Args &&... args)
    {
        m_thread = std::thread(std::forward<Function>(f), std::forward<Args>(args)...);
    }

    /**
     * Constructor ThreadWrapper
     */
    ThreadWrapper();

    /**
     * Virtual ThreadWrapper
     */
    virtual ~ThreadWrapper();

    /**
     * Move Constructor for ThreadWrapper
     *
     * @param other: Other ThreadWrapper object
     */
    ThreadWrapper(ThreadWrapper &&other) noexcept;

    /**
     * Move assignment operator for ThreadWrapper
     *
     * @param other: Other ThreadWrapper object
     * @return ThreadWrapper object
     */
    ThreadWrapper& operator=(ThreadWrapper &&other) noexcept;

    /**
     * Checks if the thread is joinable
     *
     * @return: boolean
     */
    bool joinable() const;

    /**
     * Joins the current thread
     */
    void join();

    /**
     * Detaches the current thread
     */
    void detach();

    // Deleted copy constructor and assignment operator to prevent copying
    ThreadWrapper(const ThreadWrapper &) = delete;
    ThreadWrapper &operator=(const ThreadWrapper &) = delete;

};

} // namespace butterfly

#endif //BUTTERFLY_THREADWRAPPER_H
