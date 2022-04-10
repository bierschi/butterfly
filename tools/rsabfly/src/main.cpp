#include <iostream>
#include <memory>

#include "argumentParser.h"
#include "rsa.h"
#include "utils.h"

#define RSA_PRIVATE_KEY "RSAPrivateKey.pem"
#define PUBLIC_KEY      "PublicKey.pem"
#define ENCRYPTED_FILE  "encrypted.bin"
#define RSA_EK_FILE     "rsa_ek.bin"
#define RSA_IV_FILE     "rsa_iv.txt"

void rsa_encrypt(std::string &message)
{
    std::unique_ptr<tools::CryptoRSA> cryptoRSA = std::unique_ptr<tools::CryptoRSA>(new tools::CryptoRSA(2048));

    std::string privateKeyStr = cryptoRSA->getRSAPrivateKeyStr();
    std::string pubKeyStr = cryptoRSA->getPublicKeyStr();

    // Save RSA KeyPair
    writeBinFile(RSA_PRIVATE_KEY, privateKeyStr.c_str(), privateKeyStr.length());
    writeBinFile(PUBLIC_KEY, pubKeyStr.c_str(), pubKeyStr.length());

    // Start RSA Encryption
    unsigned char *encryptedMessage = nullptr;
    int encryptedMessageLength = cryptoRSA->encryptEVP(cryptoRSA->getEvpPkey(), (const unsigned char*)message.c_str(), message.size(), &encryptedMessage);

    if(encryptedMessageLength == -1)
    {
        std::cerr << "RSA Encryption failed! Exiting..." << std::endl;
        exit(1);
    }

    // Save EK and IV (AES) for the RSA Decryption
    unsigned char* rsaek = cryptoRSA->getRSAEncryptedKey();
    unsigned char* rsaiv = cryptoRSA->getRSAIV();

    // Finally save all files
    writeBinFile(ENCRYPTED_FILE, reinterpret_cast<const char *>(encryptedMessage), encryptedMessageLength);
    writeBinFile(RSA_EK_FILE, reinterpret_cast<const char *>(rsaek), cryptoRSA->getEvpPkeySize(cryptoRSA->getEvpPkey()));
    writeBinFile(RSA_IV_FILE, reinterpret_cast<const char *>(rsaiv), EVP_MAX_IV_LENGTH);

    std::string encMessage;
    encMessage.resize(static_cast<unsigned long>(encryptedMessageLength));
    std::copy(encryptedMessage, encryptedMessage + encryptedMessageLength, encMessage.begin());
    std::cout << "Encrypting message '" << message << "' with RSA to " << encMessage << std::endl;
}

void rsa_decrypt(std::string &encryptedMessage, std::string &key, std::string &rsaek, std::string &rsaiv)
{

    std::unique_ptr<tools::CryptoRSA> cryptoRSA = std::unique_ptr<tools::CryptoRSA>(new tools::CryptoRSA(key));

    // Decrypt the encrypted Message
    char *decryptedMessage = nullptr;
    int decryptedMessageLength = cryptoRSA->decryptEVP(cryptoRSA->getEvpPkey(), (unsigned char *) encryptedMessage.c_str(), encryptedMessage.length(), (unsigned char *) rsaek.c_str(), (unsigned char *) rsaiv.c_str(), (unsigned char**)&decryptedMessage);

    if(decryptedMessageLength == -1)
    {
        std::cerr << "RSA Decryption failed! Exiting..." << std::endl;
        exit(1);
    }

    std::string str(reinterpret_cast<const char *>(decryptedMessage), static_cast<unsigned long>(decryptedMessageLength));
    std::cout << "Decrypted message is '" << str << "'" << std::endl;
}

int main(int argc, char* argv[])
{

    std::unique_ptr<tools::ArgumentParser> _argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = _argparse->parseArgs();

    if ( !args.encrypt.empty() )
    {

        if ( existsFile(args.encrypt) )
        {
            std::string message = readBinFile(args.encrypt);
            rsa_encrypt(message);
        } else
        {
            rsa_encrypt(args.encrypt);
        }

    } else if ( !args.decrypt.empty() )
    {
        if ( !args.ekivpair.empty() )
        {
            if ( !existsFile(args.ekivpair) )
            {
                std::cerr << "File " << args.ekivpair << " does not exist!" << std::endl;
                exit(1);
            } else
            {
                std::string encMessage, key, rsaekivpair, rsaek, rsaiv;
                if ( !existsFile(args.decrypt) )
                {
                    std::cerr << "File " << args.decrypt << " does not exist!" << std::endl;
                    exit(1);
                } else
                {
                    encMessage = readBinFile(args.decrypt);
                }

                if ( !existsFile(args.key) )
                {
                    std::cerr << "File " << args.key << " does not exist!" << std::endl;
                    exit(1);
                } else
                {
                    key = readBinFile(args.key);
                }

                if ( !existsFile(args.ekivpair) )
                {
                    std::cerr << "File " << args.ekivpair << " does not exist!" << std::endl;
                    exit(1);
                } else
                {
                    rsaekivpair = readBinFile(args.ekivpair);
                    int ivlen = 16;
                    int rsaKeylen = 2048/8;
                    // TODO: works only with RSA Keysize of 2048
                    rsaiv = rsaekivpair.substr(rsaekivpair.length() - (rsaKeylen + ivlen) - ivlen, rsaekivpair.length() - (rsaKeylen + ivlen));
                    rsaek = rsaekivpair.substr(0, rsaekivpair.length() - (rsaKeylen + ivlen) - ivlen);
                }

                rsa_decrypt(encMessage, key, rsaek, rsaiv);
            }

        } else
        {
            std::string encMessage, key, rsaek, rsaiv;
            if ( !existsFile(args.decrypt) )
            {
                std::cerr << "File " << args.decrypt << " does not exist!" << std::endl;
                exit(1);
            } else
            {
                encMessage = readBinFile(args.decrypt);
            }

            if ( !existsFile(args.key) )
            {
                std::cerr << "File " << args.key << " does not exist!" << std::endl;
                exit(1);
            } else
            {
                key = readBinFile(args.key);
            }

            if ( !existsFile(args.ek) )
            {
                std::cerr << "File " << args.ek << " does not exist!" << std::endl;
                exit(1);
            } else
            {
                rsaek = readBinFile(args.ek);
            }

            if ( !existsFile(args.iv) )
            {
                std::cerr << "File " << args.iv << " does not exist!" << std::endl;
                exit(1);
            }
            else
            {
                rsaiv = readBinFile(args.iv);
            }

            rsa_decrypt(encMessage, key, rsaek, rsaiv);
        }

    }

    return 0;
}

