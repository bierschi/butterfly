#include <memory>
#include <gtest/gtest.h>

#include "socket.h"

/**
 * Testclass Socket
 */
class Socket : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::Socket> _socket;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
