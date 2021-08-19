#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesDecryptor.h"

/**
 * Testclass AESDecryptorTest
 */
class AESDecryptorTest : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::aes::AESDecryptor> _aesDecryptor;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

