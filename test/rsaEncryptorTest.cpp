#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsaEncryptor.h"

/**
 * Testclass RSAEncryptorTest
 */
class RSAEncryptorTest : public ::testing::Test
{

    protected:
    std::shared_ptr<butterfly::RSAEncryptor> _rsaEncryptor;

    void SetUp() override
    {

    }

    void TearDown() override
    {

    }
};

/**
 * Testcase
 */
TEST_F(RSAEncryptorTest, Encryption)
{

}