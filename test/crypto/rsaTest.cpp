#include <memory>
#include <gtest/gtest.h>

#include "crypto/rsa.h"
#include "bflyUtils.h"

std::string privateKeyStr = "-----BEGIN RSA PRIVATE KEY-----\n"
                   "MIIEpAIBAAKCAQEA3xdLPUp/uwHy4OlpGDv8q0BHMLF3p2nq8GSKuDTePC2ScX6O\n"
                   "3z7I8uOCJIyO9Tww+a0XG7ACi38455FyrRMBgHxQr/K0AySfvqmq7952tOclHWUk\n"
                   "Qy3yIhIlN/pw0TDPXd8IbjnomfVlyQi4bKERmHB8a+X7rJab9mnvEPWWxYKq4mTD\n"
                   "4X/80LhKdguhcLL+DuVqIKN9z2GQZyKk+KhSXu5yO+U2L0rFUA4Y7nMc4fHqmOUD\n"
                   "593g/VdZLOiu5WcST0KP2c1imO4oJPF8Bi8VsAlSWqhkeWWTjKyPXo+qMp30vdIW\n"
                   "UhEQNwFDQVG4m0HfLZqv+cIGSWLsCcLRgWnhLQIDAQABAoIBAE8Me/aNzVDAUgVr\n"
                   "73dM2iz8K72PRKynlT31AkpfQVfldfyNMabdImsePmEhBQ7Ucy4lLQj8hwpS3CEB\n"
                   "ora9A005v4V45FwwwAHZMN6p3zoepUITMpQzVZbJAzMgpJUbTH8gpmYYUtkq4RQo\n"
                   "6OBk+k0fnpbE+Tagb0cTJkjGHNSC3PqGYDr76ZNAIMrQMeGRkxR3q8Xuh4dfgpLf\n"
                   "lJZMTuH8vIzPAJCOyUc1VLFIRG6pVQ4Q5amb4rY6F2SbGdVCmuWKzQx6gPQ04uWX\n"
                   "BqJcJobl8nwDRIUUxasK18XNHbX2zkECqzuYQ7UrVKEVrCwjhTsaGfg8L+2ZOQk3\n"
                   "6j52HekCgYEA+EWW62mUeXDDJNruno9M8TXHrmfWZNTrW0f+pcdOYiFe+sJaq5/5\n"
                   "Z94LSHPn9nwtG3YDkmlkn07kkFY5YLXVdmgZbc7F/pTq8GUhUp3EhYouoQuxjQok\n"
                   "1W+fxtTYa8ngeYbwcJY+2MnaZQ7WcpSJewiT71BUoehHJdIPmnhejUMCgYEA5gkL\n"
                   "jL2L0YW6rMtSUNhSIjZTufC71wL7nvK2SqokjA0DyUzVKKY1+68wCTk/qRw4FFoL\n"
                   "n8+5yaaL23vMGGgYXXBvammqAFnCXL2b8xDxZjNuPrmiraCrn5Q2zEdt9h+qzd/k\n"
                   "RLglCWVyE3uW7hQg/n8IrlYP1yRPLvDkrLlFOM8CgYEAuHVbsAR9n8y78EIJUB1A\n"
                   "GWbPuTDFBZ18UBGpjRoLjrUkkEKegy0UbKt4zpfvHB8elGyWMs3DSOmgv+yQLN5s\n"
                   "ftDRM9iRGpkiBQHeRDebr2v/QQAjJpsGyt1oZJ33Pf57nU84jS3T+9XdQYBIrFDX\n"
                   "5GV3JDMW7kRZuCveE/KirWkCgYABbNDrgEkbdS6g32mVIqHvoFKIdltTi6svYuWK\n"
                   "NN+hFnuNhbJUXCM9eepcRESGsawPRDeKN+k4vJVlOLEc/ZgZDBdEm374HZY8qNgM\n"
                   "e3BjZ7IpJVFCrhoiFPL59P9TZQLT3600V8ey9TPttvhKZUmHChZtrg7PEGSFL+za\n"
                   "vRMWtQKBgQDVpBHsKqHlvtURUT4JtgRHwRn74T251Lskx5Xwu/aMUm44hAlB/qK9\n"
                   "OKRz4eG+kZXt/8TeepH8YPC2uDfBtiTwW01N/u/4AZR5Wm8RWW+IERFpGt2iDUxm\n"
                   "UlujLxvA0pPWC9DISxUuy1Lpb+ZbMBlKOyP6q7JDaFbh/JOVRvpQ1A==\n"
                   "-----END RSA PRIVATE KEY-----";

/**
 * Testclass CryptoRSATest
 */
class CryptoRSATest : public ::testing::Test
{

protected:
    int rsaKeysize = 2048;
    std::string msg_to_encrypt = "abcdef";
    std::unique_ptr<butterfly::rsa::CryptoRSA> cryptoRSA;

    std::string encryptedMessageHex = "c4e4c3c648b2aa0e8671c2fd3eeab962";
    std::string rsaekHex = "149575f33b14e8395b4df38bc4250eb87da447726312774670684685c20a5edc019d640a334a0ac89f60394184358d2156c45d3db95c32b669902ddf28ce57adf030dc0b2c6ee504782cd27b02a77228d051d98b62c05f84cb47d503cf7aff36dc5f36607fc160c55c6f66f6b2bc7dab357239a10d0b06ff4f3654010f2cadb42a5c0d547ca91ef8a0ef0eeeafad725ab1c7cc1f5ce069104ce37add9194dc388376ef5ccb4bed07b3e3bb7d69ef8dc6ba319a448ceb13e302f49c93b8f39841902d2cbcaf63e62d3fbdb2e69505dd9b79199f9fdc3a7f8fe4b0770d05d82f3a2f6e419218206aa786eb609f8d5f4fd5d024b4701d05808c671753619f3d30c1";
    std::string rsaivHex = "5b7165e658874669e3d6a2c7d5a26099";
    std::unique_ptr<butterfly::rsa::CryptoRSA> cryptoRSADec;

    void SetUp() override
    {
        cryptoRSA = std::unique_ptr<butterfly::rsa::CryptoRSA>(new butterfly::rsa::CryptoRSA(rsaKeysize));
        cryptoRSADec = std::unique_ptr<butterfly::rsa::CryptoRSA>(new butterfly::rsa::CryptoRSA(privateKeyStr));
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
#if (OPENSSL_VERSION_NUMBER < 0x30000000L)
TEST_F(CryptoRSATest, getRSAPrivateKeyStr)
{
    std::string rsaPrivateKey = cryptoRSA->getRSAPrivateKeyStr();

    std::string fLine;
    std::istringstream f(rsaPrivateKey);
    std::getline(f, fLine);

    EXPECT_TRUE( fLine == "-----BEGIN RSA PRIVATE KEY-----");
}
#endif

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

    /*
    unsigned char* rsaek = cryptoRSA->getRSAEncryptedKey();
    unsigned char* rsaiv = cryptoRSA->getRSAIV();

    std::string encMSG(reinterpret_cast<const char *>(encryptedMessage), static_cast<unsigned long>(encryptedMessageLength));
    std::string rsaekStr(reinterpret_cast<const char *>(rsaek), static_cast<unsigned long>(rsaKeysize / 8));
    std::string rsaivStr(reinterpret_cast<const char *>(rsaiv), EVP_MAX_IV_LENGTH);

    std::string encMSGHex = butterfly::string2Hex(encMSG);
    std::string rsaekHex = butterfly::string2Hex(rsaekStr);
    std::string rsaivHex = butterfly::string2Hex(rsaivStr);

    std::cout << "PRIVKey: " << privateKeyStr << std::endl;
    std::cout << "ENCMSG: " << butterfly::string2Hex(encMSG) << std::endl;
    std::cout << "RSAEK: " << butterfly::string2Hex(rsaekStr) << std::endl;
    std::cout << "RSAIV: " << butterfly::string2Hex(rsaivStr) << std::endl;
    */
}

/**
 * Testcase for testing the getRSAIV
 */
TEST_F(CryptoRSATest, getRSAIV)
{
   std::string rsaiv = reinterpret_cast<const char *>(cryptoRSA->getRSAIV());
   EXPECT_TRUE(!rsaiv.empty());
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

TEST_F(CryptoRSATest, decryptEVP)
{

    std::string encryptedMessage = butterfly::hex2String(encryptedMessageHex);
    std::string rsaek = butterfly::hex2String(rsaekHex);
    std::string rsaiv = butterfly::hex2String(rsaivHex);

    char *decryptedMessage = nullptr;
    int decryptedMessageLength = cryptoRSADec->decryptEVP(cryptoRSADec->getEvpPkey(), (unsigned char *) encryptedMessage.c_str(), encryptedMessage.length(), (unsigned char *) rsaek.c_str(), (unsigned char *) rsaiv.c_str(), (unsigned char**)&decryptedMessage);

    std::string dec(reinterpret_cast<const char *>(decryptedMessage), static_cast<unsigned long>(decryptedMessageLength));

    EXPECT_TRUE(dec == msg_to_encrypt);
}