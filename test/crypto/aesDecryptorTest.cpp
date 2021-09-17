#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesDecryptor.h"

/**
 * Testclass AESDecryptorTest
 */
class AESDecryptorTest : public ::testing::Test
{

protected:
    std::string _aeskey = "0123456789abcefghijklmnopqrstuvw", _aesiv = "0123456789abcefg";
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
 * Testcase for testing the AES Key/IV Setter/Getter
 */
TEST_F(AESDecryptorTest, AESKEYPair)
{

    aesDecryptor->generateAESKeyWithSalt();
    aesDecryptor->setAESKey(_aeskey);
    aesDecryptor->setAESIv(_aesiv);

    std::string aeskey = aesDecryptor->getAESKey();
    std::string aesiv = aesDecryptor->getAESIv();

    EXPECT_TRUE( aeskey == _aeskey);
    EXPECT_TRUE( aesiv == _aesiv);
}

/**
 * Testcase for decrypting a file
 */
TEST_F(AESDecryptorTest, DecryptFile)
{

    aesDecryptor->setAESKey(_aeskey);
    aesDecryptor->setAESIv(_aesiv);

    aesDecryptor->decryptFile("../test/crypto/testfile.pdf" + butterfly::ENC_BFLY_FILE_ENDING);
}