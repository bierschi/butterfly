#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsa.h"

/**
 * Testclass CryptoRSATest
 */
class CryptoRSATest : public ::testing::Test
{

protected:
    int rsaKeysize = 2048;
    std::string msg_to_encrypt = "abcdef";
    std::unique_ptr<butterfly::rsa::CryptoRSA> cryptoRSA;

    void SetUp() override
    {
        cryptoRSA = std::unique_ptr<butterfly::rsa::CryptoRSA>(new butterfly::rsa::CryptoRSA(rsaKeysize));
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for testing the getEvpPkeySize
 */
TEST_F(CryptoRSATest, getEvpPkeySize)
{
    int keysize = cryptoRSA->getEvpPkeySize(cryptoRSA->getEvpPkey());
    EXPECT_TRUE( keysize == rsaKeysize/8);
    EXPECT_FALSE(keysize == rsaKeysize/8 +1);
}

/**
 * Testcase for testing the getRSAPrivateKeyStr
 */
TEST_F(CryptoRSATest, getRSAPrivateKeyStr)
{
    std::string rsaPrivateKey = cryptoRSA->getRSAPrivateKeyStr();

    std::string fLine;
    std::istringstream f(rsaPrivateKey);
    std::getline(f, fLine);

    EXPECT_TRUE( fLine == "-----BEGIN RSA PRIVATE KEY-----");
}

/**
 * Testcase for testing the getPrivateKeyStr
 */
TEST_F(CryptoRSATest, getPrivateKeyStr)
{
    std::string privateKey = cryptoRSA->getPrivateKeyStr();
    std::string fLine;
    std::istringstream f(privateKey);
    std::getline(f, fLine);

    EXPECT_TRUE( fLine == "-----BEGIN PRIVATE KEY-----");
}

/**
 * Testcase for testing the getPublicKeyStr
 */
TEST_F(CryptoRSATest, getPublicKeyStr)
{
    std::string publicKey = cryptoRSA->getPublicKeyStr();
    std::string fLine;
    std::istringstream f(publicKey);
    std::getline(f, fLine);

    EXPECT_TRUE( fLine == "-----BEGIN PUBLIC KEY-----");
}

/**
 * Testcase for testing the encryptEVP
 */
TEST_F(CryptoRSATest, encryptEVP)
{
    unsigned char *encryptedMessage = nullptr;
    int encryptedMessageLength = cryptoRSA->encryptEVP(cryptoRSA->getEvpPkey(), (const unsigned char*)msg_to_encrypt.c_str(), msg_to_encrypt.size(), &encryptedMessage);

    EXPECT_FALSE(encryptedMessageLength == -1);
    EXPECT_TRUE(encryptedMessage != nullptr);
}

/**
 * Testcase for testing the getRSAIV
 */
TEST_F(CryptoRSATest, getRSAIV)
{
   std::string rsaiv = reinterpret_cast<const char *>(cryptoRSA->getRSAIV());
   EXPECT_TRUE( rsaiv.length() == EVP_MAX_IV_LENGTH);
   EXPECT_FALSE(rsaiv.length() == 17);
}

/**
 * Testcase for testing the getRSAEncryptedKey
 */
TEST_F(CryptoRSATest, getRSAEncryptedKey)
{
   std::string rsaek = reinterpret_cast<const char *>(cryptoRSA->getRSAEncryptedKey());
   EXPECT_TRUE( !rsaek.empty());
}

/**
 * Testcase for testing the decryptEVP
 */
 /*
TEST_F(CryptoRSATest, decryptEVP)
{
    std::string encryptedMessage = readBinFile(ENCRYPTED_FILE);
    std::string rsaek = readBinFile(RSA_EK_FILE);
    std::string rsaiv = readBinFile(RSA_IV_FILE);

    char *decryptedMessage = nullptr;
    int decryptedMessageLength = cryptoRSA->decryptEVP(cryptoRSA->getEvpPkey(), (unsigned char *) encryptedMessage.c_str(), encryptedMessage.length(), (unsigned char *) rsaek.c_str(), (unsigned char *) rsaiv.c_str(), (unsigned char**)&decryptedMessage);

}*/