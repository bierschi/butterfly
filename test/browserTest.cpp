#include <memory>
#include <gtest/gtest.h>

#include "browser.h"

/**
 * Testclass BrowserTest
 */
class BrowserTest : public ::testing::Test
{

protected:
    std::string url, terminalCMD;
    std::shared_ptr<butterfly::Browser> browser;
    std::shared_ptr<butterfly::Browser> browserException;

    void SetUp() override
    {
        url = "http://127.0.0.1:8080";
        terminalCMD = "x-www-browser";
        browser = std::make_shared<butterfly::Browser>(terminalCMD);
        browserException = std::make_shared<butterfly::Browser>(terminalCMD.substr(0, terminalCMD.size()-1));
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the open method
 */
TEST_F(BrowserTest, open)
{
    // this tests that the expected exception is thrown
    EXPECT_THROW({
                     try
                     {

                         browserException->open(url, true);
                     }
                     catch( const butterfly::BrowserException &e )
                     {
                         // and this tests that it has the correct message
                         std::string s = "Error at executing command " + terminalCMD.substr(0, terminalCMD.size()-1) + " " + url;
                         EXPECT_STREQ( s.c_str(), e.what() );
                         throw;
                     }
                 }, butterfly::BrowserException );

}
