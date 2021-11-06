#include <memory>
#include <gtest/gtest.h>

#include "httpServer.h"

/**
 * Testclass HTTPServer
 */
class HTTPServer : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::HTTPServer> _httpServer;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
