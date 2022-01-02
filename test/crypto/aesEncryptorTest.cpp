#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesEncryptor.h"
#include "bflyUtils.h"

#define ORIGFILE "../test/crypto/5357083.pdf"
#define TESTFILE "../test/crypto/testfile.pdf"

bool copyFile()
{
    std::ifstream src;
    std::ofstream dst;

    if ( butterfly::existsFile(ORIGFILE) )
    {
        src.open(ORIGFILE, std::ios::in | std::ios::binary);
        dst.open(TESTFILE, std::ios::out | std::ios::binary);
        dst << src.rdbuf();
        src.close();
        dst.close();

        return true;
    } else
    {
        return false;
    }
}

/**
 * Testclass AESEncryptorTest
 */
class AESEncryptorTest : public ::testing::Test
{

protected:
    std::string aeskeyTest = "0123456789abcefghijklmnopqrstuvw", aesivTest = "0123456789abcefg";
    std::unique_ptr<butterfly::aes::AESEncryptor> aesEncryptor;

    void SetUp() override
    {
        aesEncryptor = std::unique_ptr<butterfly::aes::AESEncryptor>(new butterfly::aes::AESEncryptor());
        if ( copyFile() )
        {
            std::cout << "Copied file successfully" << std::endl;
        } else
        {
            std::cerr << "Error on copying file!" << std::endl;
        }
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for encrypting a file with AES
 */
TEST_F(AESEncryptorTest, encryptFile)
{
    aesEncryptor->setAESKey(aeskeyTest);
    aesEncryptor->setAESIv(aesivTest);

    aesEncryptor->encryptFile(TESTFILE);
}
