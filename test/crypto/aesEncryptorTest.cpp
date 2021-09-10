#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesEncryptor.h"

/**
 * Testclass AESEncryptorTest
 */
class AESEncryptorTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::aes::AESEncryptor> aesEncryptor;

    void SetUp() override
    {
        aesEncryptor.reset(new butterfly::aes::AESEncryptor());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for generating AESKey
 */
TEST_F(AESEncryptorTest, generateAESKey)
{
    aesEncryptor->generateAESKey();

}

/**
 * Testcase for encrypting a file
 */
TEST_F(AESEncryptorTest, EncryptFile)
{
    aesEncryptor->setAESKey("abc");
    aesEncryptor->setAESIv("def");

    //aesEncryptor->encryptFile("../notes/papers/5357083.pdf");
}