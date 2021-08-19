#include <memory>
#include <gtest/gtest.h>

#include "crypto/aes.h"

/**
 * Testclass CryptoAESTest
 */
class CryptoAESTest : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::aes::CryptoAES> _cryptoAES;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

