#include <memory>
#include <gtest/gtest.h>

#include "httpResponse.h"

/**
 * Testclass HTTPResponse
 */
class HTTPResponse : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::HTTPResponse> _httpResponse;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};
