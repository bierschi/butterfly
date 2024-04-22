#include "threadWrapper.h"

namespace butterfly {

ThreadWrapper::ThreadWrapper() : m_thread()
{

}

ThreadWrapper::~ThreadWrapper()
{
    if ( m_thread.joinable() )
    {
        m_thread.join();
    }
}

ThreadWrapper::ThreadWrapper(ThreadWrapper &&other) noexcept: m_thread(std::move(other.m_thread))
{

}

ThreadWrapper &ThreadWrapper::operator=(ThreadWrapper &&other) noexcept
{
    if ( joinable() )
    {
        m_thread.join();
    }

    m_thread = std::move(other.m_thread);

    return *this;
}

bool ThreadWrapper::joinable() const
{
    return m_thread.joinable();
}

void ThreadWrapper::join()
{
    if ( joinable() )
    {
        m_thread.join();
    }
}

void ThreadWrapper::detach()
{
    if ( joinable() )
    {
        m_thread.detach();
    }
}

} // namespace butterfly
