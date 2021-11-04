#include <memory>
#include <gtest/gtest.h>

#include "httpRequest.h"

/**
 * Testclass HTTPRequest
 */
class HTTPRequest : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::HTTPRequest> _httpRequest;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
