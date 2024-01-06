
#include "crypto/decryptor.h"

namespace butterfly
{

namespace hybrid
{

Decryptor::Decryptor(const std::string &decryptedCPrivateRSA) : _decryptedCPrivateRSA(decryptedCPrivateRSA), _rsaDecryptorAESKey(new rsa::RSADecryptor(_decryptedCPrivateRSA)),
                                                                                                             _aesDecryptor(new aes::AESDecryptor())
{
    #ifdef LOGGING
    LOG_TRACE("Create class Decryptor");
    #endif
}

Decryptor::Decryptor(const std::string &privateKeyFromServer, const std::string &encCPrivateRSAFile) : _privateKeyFromServer(privateKeyFromServer), _encCPrivateRSAFile(encCPrivateRSAFile),
                                                                                                       _rsaDecryptorCPrivateRSA(new rsa::RSADecryptor(_privateKeyFromServer)),
                                                                                                       _aesDecryptor(new aes::AESDecryptor())
{
    #ifdef LOGGING
    LOG_TRACE("Create class Decryptor");
    #endif

    try
    {
        std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->readEncMSGFromFile(_encCPrivateRSAFile);
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
    if ( (_decryptedCPrivateRSA.find("-----BEGIN PRIVATE KEY-----") == std::string::npos) && (_decryptedCPrivateRSA.find("-----BEGIN RSA PRIVATE KEY-----") == std::string::npos) )
    {
        throw DecryptorException("Decrypted CPrivateRSA String does not include '-----BEGIN RSA PRIVATE KEY-----' or '-----BEGIN PRIVATE KEY-----'");
    }

    _rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));
}

void Decryptor::invokeDir(const std::string &dirPath)
{

    // Ensure the decrypted CPrivateRSA string is available
    if ( _decryptedCPrivateRSA.empty() )
    {
        throw DecryptorException("Could not start the decryption process, because decrypted CPrivateRSA.pem string is empty!");
    }

    // Check if dirPath exists
    if ( !DirectoryIterator::exists(dirPath) )
    {
        throw DecryptorException("Provided Directory Path " + dirPath + " doesn´t exists!");
    }

    // Decrypt the AESKey.bin file and get AESKey and AESIV
    std::string aeskey, aesiv;
    decryptAESKeyPair(butterfly::params::ENC_AESKEY_FILENAME, aeskey, aesiv);

    // Set static AESKey and AESIV
    _aesDecryptor->setAESKey(aeskey);
    _aesDecryptor->setAESIv(aesiv);

    // Get all files from provided directory path
    auto files = DirectoryIterator::getAllFiles(dirPath);

    // Iterate over all file paths
    for (auto &file: files)
    {
        // Check if the provided file path has the .bfly extension
        if ( DirectoryIterator::getFileExtension(file) == butterfly::params::ENC_BFLY_FILE_ENDING )
        {
            // Compare file size with the MAX FILE SIZE
            if ( butterfly::getFileSize(file.string(), true) > butterfly::params::MAX_FILE_SIZE)
            {
                #ifdef LOGGING
                LOG_TRACE("Spawn a new decryption thread for file: " << file.string());
                #endif
                CryptoThread::create(file.string());
            } else
            {
                decryptFileWithAES(file.string());
            }
        }

    }

    // Join all threads which were spawned for large file decryption
    CryptoThread::joinThreads();

    // Remove decryption helper files
    CryptoSecurity::removeDecryptedFiles();
}

void Decryptor::decryptAESKeyPair(const std::string &filepathAESKey, std::string &decAESKey,  std::string &decAESIV)
{
    std::string aeskeypair;

    try
    {

        std::string encAESKey = _rsaDecryptorAESKey->readEncMSGFromFile(filepathAESKey);  // Length of encAESKey = encMSGLen in encrypt

        _rsaDecryptorAESKey->decryptEVP(_rsaDecryptorAESKey->getEvpPkey(), encAESKey, aeskeypair, butterfly::RSAKEY_TYPE::AESKEY);
        //rsaDecryptorAESKey->decrypt(rsaDecryptorAESKey->getEvpPkey(), encAESKey, aeskeypair);
        #ifdef LOGGING
        LOG_TRACE("Decrypted Content from file " << filepathAESKey << ": " << aeskeypair << " with Length: " << aeskeypair.length());
        #endif
        //std::cout << "Decrypted Content from file " << filepathAESKey << ": " << aeskeypair << " with Length: " << aeskeypair.length() << std::endl;

    } catch (RSADecryptionException &e)
    {
        std::cerr << e.what() << std::endl;

        // If error occurred here, check first whether unencrypted AESKeyPair file exists
        if ( !CryptoSecurity::getAESKeyPairFromUnencryptedFile(aeskeypair) )
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
    }

}

void Decryptor::handleLargeFilesWithAES(const std::string &filepath)
{
    // Create new instance for each large file
    std::unique_ptr<aes::AESDecryptor> aesDecInstance = std::unique_ptr<aes::AESDecryptor>(new aes::AESDecryptor());
    try
    {
        // Decrypt the file with AES
        aesDecInstance->decryptLargeFile(filepath);

    } catch (AESDecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
    }
}

} // namespace hybrid

} // namespace butterfly
