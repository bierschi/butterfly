#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesDecryptor.h"

/**
 * Testclass AESDecryptorTest
 */
class AESDecryptorTest : public ::testing::Test
{

protected:
    std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor;

    void SetUp() override
    {
        aesDecryptor.reset(new butterfly::aes::AESDecryptor());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the aeskey/aesiv setter
 */
TEST_F(AESDecryptorTest, AESKEY_IV)
{
    aesDecryptor->generateAESKey();
    aesDecryptor->setAESKey("abc");

    std::string aesk = aesDecryptor->getAESKey();
    EXPECT_TRUE( aesk == "abc");

    aesDecryptor->setAESIv("def");
    std::string aesiv = aesDecryptor->getAESIv();
    EXPECT_TRUE( aesiv == "def");
}

/**
 * Testcase for decrypting a file
 */
TEST_F(AESDecryptorTest, EncryptFile)
{

    aesDecryptor->setAESKey("abc");
    aesDecryptor->setAESIv("def");

    //aesDecryptor->decryptFile("../notes/papers/5357083.pdf");
}