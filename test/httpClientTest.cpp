#include <memory>
#include <gtest/gtest.h>

#include "httpClient.h"

/**
 * Testclass HTTPClient
 */
class HTTPClientTest : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::HTTPClient> httpClient;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};