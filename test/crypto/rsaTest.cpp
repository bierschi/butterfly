#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsa.h"

/**
 * Testclass CryptoRSATest
 */
class CryptoRSATest : public ::testing::Test
{

protected:

    std::shared_ptr<butterfly::rsa::CryptoRSA> _cryptoRSAFromStr;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

