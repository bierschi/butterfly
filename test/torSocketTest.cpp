#include <memory>
#include <gtest/gtest.h>

#include "torSocket.h"

/**
 * Testclass TORSocket
 */
class TORSocketTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::TORSocket> torSocket;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

