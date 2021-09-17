#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesEncryptor.h"

/**
 * Testclass AESEncryptorTest
 */
class AESEncryptorTest : public ::testing::Test
{

protected:
    std::string _aeskey = "0123456789abcefghijklmnopqrstuvw", _aesiv = "0123456789abcefg";
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
 * Testcase for testing the AESKey
 */
TEST_F(AESEncryptorTest, AESKey)
{
    aesEncryptor->generateAESKeyWithSalt();
    std::string aeskey = aesEncryptor->getAESKey();
    EXPECT_TRUE( aeskey.length() == 32);
}

/**
 * Testcase for testing the AESIV
 */
TEST_F(AESEncryptorTest, AESIV)
{
    aesEncryptor->generateAESKeyWithSalt();
    std::string aesiv = aesEncryptor->getAESIv();
    EXPECT_TRUE( aesiv.length() == 16);
}

/**
 * Testcase for testing the AESKeyPair
 */
TEST_F(AESEncryptorTest, AESKeyPair)
{
    aesEncryptor->generateAESKeyWithSalt();
    std::string aeskeypair = aesEncryptor->getAESKeyPair();
    EXPECT_TRUE( aeskeypair.length() == 48);
}

/**
 * Testcase for testing the AESKeyLength
 */
TEST_F(AESEncryptorTest, AESKeyLength)
{
    aesEncryptor->generateAESKeyWithSalt();
    int aeskeyLength = aesEncryptor->getAESKeyLength();
    EXPECT_TRUE( aeskeyLength == 32);
}

/**
 * Testcase for testing the AESIVLength
 */
TEST_F(AESEncryptorTest, AESIVLength)
{
    aesEncryptor->generateAESKeyWithSalt();
    int aesivLength = aesEncryptor->getAESIVLength();
    EXPECT_TRUE( aesivLength == 16);
}

/**
 * Testcase for encrypting a file
 */
TEST_F(AESEncryptorTest, EncryptFile)
{
    aesEncryptor->setAESKey(_aeskey);
    aesEncryptor->setAESIv(_aesiv);

    aesEncryptor->encryptFile("../test/crypto/testfile.pdf");
}