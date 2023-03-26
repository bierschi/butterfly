#include <memory>
#include <gtest/gtest.h>

#include "httpRequest.h"
#include "bflyParams.h"

/**
 * Testclass HTTPRequestTest
 */
class HTTPRequestTest : public ::testing::Test
{

protected:
    std::string _url = "www.google.de", _userAgent = "butterfly", _contentType = "application/x-www-form-urlencoded", _testRoute = "/testroute", _formParamStr;
    butterfly::Method _method = butterfly::Method::POST;
    butterfly::Protocol _protocol = butterfly::Protocol::HTTP1_1;
    std::vector< std::pair<std::string, std::string> > _formParams;
    std::unique_ptr<butterfly::HTTPRequest> httpRequest;

    void SetUp() override
    {
        httpRequest = std::unique_ptr<butterfly::HTTPRequest>(new butterfly::HTTPRequest());
        // Set http request data
        httpRequest->setURL(_url);
        httpRequest->setMethod(_method);
        httpRequest->setProtocol(_protocol);
        httpRequest->setHTTPHeader("User-Agent", _userAgent);
        httpRequest->setHTTPHeader("Content-Type", _contentType);

        _formParams.emplace_back(butterfly::params::ENC_CPRIVATERSA_FILENAME, "abcdef123");
        _formParams.emplace_back(butterfly::params::RSA_EKIV_FILENAME, "abcdef123");
        _formParams.emplace_back("RSAKeySize", std::to_string(butterfly::params::RSA_KEYSIZE));

        httpRequest->addFormParamVector(_formParams);
        _formParamStr = httpRequest->getFormParam();
        httpRequest->addBody(_formParamStr);
        httpRequest->setHTTPHeader("Content-Length", std::to_string(httpRequest->getBody().length()));

        httpRequest->prepareOutgoing();
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the getMethod method
 */
TEST_F(HTTPRequestTest, getMethod)
{
    butterfly::Method method = httpRequest->getMethod();

    EXPECT_TRUE(method == _method);
}

/**
 * Testcase for testing the getURL method
 */
TEST_F(HTTPRequestTest, getURL)
{
    std::string url = httpRequest->getURL();

    EXPECT_TRUE(url == _url);
}

/**
 * Testcase for testing the getUserAgent method
 */
TEST_F(HTTPRequestTest, getUserAgent)
{
    httpRequest->setUserAgent(_userAgent);
    std::string useragent = httpRequest->getUserAgent();

    EXPECT_TRUE(useragent == _userAgent);
}

/**
 * Testcase for testing the getRoute method
 */
TEST_F(HTTPRequestTest, getRoute)
{
    httpRequest->setRoute(_testRoute);
    std::string route = httpRequest->getRoute();

    EXPECT_TRUE(route == _testRoute);
}

/**
 * Testcase for testing the getRequestSize
 */
TEST_F(HTTPRequestTest, getRequestSize)
{
    size_t httpDatasize = httpRequest->getHTTPDataSize();

    EXPECT_TRUE( httpDatasize > 0);
}

/**
 * Testcase for testing the getHTTPData
 */
TEST_F(HTTPRequestTest, getHTTPData)
{
    std::string httpdata = httpRequest->getHTTPData();

    EXPECT_TRUE( !httpdata.empty() );
}

/**
 * Testcase for testing the getProtocol
 */
TEST_F(HTTPRequestTest, getProtocol)
{

    butterfly::Protocol prot = httpRequest->getProtocol();

    EXPECT_TRUE(prot == _protocol);
}

/**
 * Testcase for testing the getBody
 */
TEST_F(HTTPRequestTest, getBody)
{
    std::string body = httpRequest->getBody();

    EXPECT_TRUE(body == _formParamStr);
}

/**
 * Testcase for testing the getHTTPHeader
 */
TEST_F(HTTPRequestTest, getHTTPHeader)
{
    std::string httpHeaderUserAgent = httpRequest->getHTTPHeader("User-Agent");
    std::string httpHeaderContentType = httpRequest->getHTTPHeader("Content-Type");

    EXPECT_TRUE(httpHeaderUserAgent == _userAgent);
    EXPECT_TRUE(httpHeaderContentType == _contentType);
}
