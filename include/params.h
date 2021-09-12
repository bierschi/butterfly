
#ifndef BUTTERFLY_PARAMS_H
#define BUTTERFLY_PARAMS_H

namespace butterfly
{

enum RSAKEY_TYPE { CPRIVATE_RSA, AESKEY };

// Filename CPrivateRSA.bin
const std::string ENC_CPRIVATERSA_FILENAME   = "CPrivateRSA.bin";

// Filename AESKey.bin
const std::string ENC_AESKEY_FILENAME        = "AESKey.bin";

// Filename RSAEKIV.bin
const std::string RSA_EKIV_FILENAME          = "RSAEKIV.bin";

const std::string ENC_BFLY_FILE_ENDING       = ".bfly";

} // namespace butterfly

#endif //BUTTERFLY_PARAMS_H
