
#include <memory>

#include "crypto/decryptor.h"

namespace butterfly
{

namespace hybrid
{

Decryptor::Decryptor(const std::string &aesKeyDbFilepath) : _aesKeyDbFilepath(aesKeyDbFilepath), _aesDecryptor(new aes::AESDecryptor())
{
    LOG_TRACE("Create class Decryptor");
}

void Decryptor::removeDecryptedFiles()
{

    butterfly::removeFile(butterfly::ENC_CPRIVATERSA_FILENAME);
    butterfly::removeFile(butterfly::ENC_AESKEY_FILENAME);
    butterfly::removeFile(butterfly::RSA_EKIV_FILENAME);

}

void Decryptor::invokeDir(const std::string &dirPath, const std::string &pkeyFromServer)
{
    // Decrypt the CPrivateRSA.bin file
    decryptCPrivateRSA(pkeyFromServer, butterfly::ENC_CPRIVATERSA_FILENAME);

    // Decrypt the AESKey.bin file and get AESKey and AESIV
    std::string aesk, aesiv;
    decryptAESKeyPair(butterfly::ENC_AESKEY_FILENAME, aesk, aesiv);

    auto files = DirectoryIterator::getAllFiles(dirPath);
    for (auto &file: files)
    {
        std::string filepath = file.string();
        decryptFileWithAES(filepath, aesk, aesiv);
    }

    removeDecryptedFiles();
}

void Decryptor::decryptCPrivateRSA(const std::string &pkeyFromServer, const std::string &encCPrivateRSAFile)
{

    _rsaDecryptorCPrivateRSA = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(pkeyFromServer));

    std::string encCPrivateRSA = _rsaDecryptorCPrivateRSA->readEncMSGFromFile(encCPrivateRSAFile);
    EVP_PKEY *CPrivateRSAPKey = _rsaDecryptorCPrivateRSA->getEvpPkey();

    try
    {
        _rsaDecryptorCPrivateRSA->decryptEVP(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA, butterfly::RSAKEY_TYPE::CPRIVATE_RSA);
        //_rsaDecryptorCPrivateRSA->decrypt(CPrivateRSAPKey, encCPrivateRSA, _decryptedCPrivateRSA);
        LOG_TRACE("Decrypted CPrivateRSA: " << _decryptedCPrivateRSA);
        //std::cout << "Decrypted CPrivateRSA: " << _decryptedCPrivateRSA << std::endl;

    } catch (RSADecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
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

    std::unique_ptr<rsa::RSADecryptor> rsaDecryptorAESKey = std::unique_ptr<rsa::RSADecryptor>(new rsa::RSADecryptor(_decryptedCPrivateRSA));

    std::string encAESKey = rsaDecryptorAESKey->readEncMSGFromFile(filepathAESKey);  // Length of encAESKey = encMSGLen in encrypt

    std::string aeskeypair;
    try
    {
        rsaDecryptorAESKey->decryptEVP(rsaDecryptorAESKey->getEvpPkey(), encAESKey, aeskeypair, butterfly::RSAKEY_TYPE::AESKEY);
        //rsaDecryptorAESKey->decrypt(rsaDecryptorAESKey->getEvpPkey(), encAESKey, aeskeypair);
        LOG_TRACE("Decrypted Content from file " << filepathAESKey << ": " << aeskeypair << " with Length: " << aeskeypair.length());
        //std::cout << "Decrypted Content from file " << filepathAESKey << ": " << aeskeypair << " with Length: " << aeskeypair.length() << std::endl;

    } catch (RSADecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
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

void Decryptor::decryptFileWithAES(const std::string &filepath, std::string &aeskey, std::string &aesiv)
{
    // Set AESKey and AESIV
    _aesDecryptor->setAESKey(aeskey);
    _aesDecryptor->setAESIv(aesiv);

    try
    {
        // Decrypt the file with AES
        _aesDecryptor->decryptFile(filepath);

    } catch (AESDecryptionException &e)
    {
        std::cerr << e.what() << std::endl;
        LOG_ERROR(e.what());
        throw DecryptorException(e.what());
    }

}

} // namespace hybrid

} // namespace butterfly
