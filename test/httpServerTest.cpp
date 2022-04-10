#include <memory>
#include <gtest/gtest.h>

#include "httpServer.h"

/**
 * Testclass HTTPServerTest
 */
class HTTPServerTest : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::HTTPServer> httpServer;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
