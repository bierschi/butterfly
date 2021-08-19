#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesEncryptor.h"

/**
 * Testclass AESEncryptorTest
 */
class AESEncryptorTest : public ::testing::Test
{

protected:
    std::shared_ptr<butterfly::aes::AESEncryptor> _aesEncryptor;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

