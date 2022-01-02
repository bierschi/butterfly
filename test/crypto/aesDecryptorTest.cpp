#include <memory>
#include <gtest/gtest.h>

#include "crypto/aesDecryptor.h"
#include "bflyUtils.h"

#define TESTFILE "../test/crypto/testfile.pdf"

/**
 * Testclass AESDecryptorTest
 */
class AESDecryptorTest : public ::testing::Test
{

protected:
    std::string aeskeyTest = "0123456789abcefghijklmnopqrstuvw", aesivTest = "0123456789abcefg";
    std::unique_ptr<butterfly::aes::AESDecryptor> aesDecryptor;

    void SetUp() override
    {
        aesDecryptor = std::unique_ptr<butterfly::aes::AESDecryptor>(new butterfly::aes::AESDecryptor());
    }

    void TearDown() override
    {

    }
};

/**
 * Testcase for decrypting a file with AES
 */
TEST_F(AESDecryptorTest, decryptFile)
{

    aesDecryptor->setAESKey(aeskeyTest);
    aesDecryptor->setAESIv(aesivTest);

    if ( butterfly::existsFile(TESTFILE + butterfly::ENC_BFLY_FILE_ENDING) )
    {
        aesDecryptor->decryptFile(TESTFILE + butterfly::ENC_BFLY_FILE_ENDING);

        if ( butterfly::existsFile(TESTFILE) )
        {
            butterfly::removeFile(TESTFILE);
        }
    } else
    {
        std::cerr << "Could not decrypt file " << TESTFILE + butterfly::ENC_BFLY_FILE_ENDING << " because file does not exists!" << std::endl;
    }

}
