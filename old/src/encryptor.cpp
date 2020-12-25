//
// Created on 28.01.20.
//

#include "../include/encryptor.h"

Encryptor::Encryptor(std::vector<boost::filesystem::path>& dirs) : _dirs(dirs), _directoryIt(new DirectoryIiterator), _rsaalgo(new RSAAlgorithm){
    std::cout << "Create Encryptor" << std::endl;
}

Encryptor::~Encryptor() {
    join();
}

void Encryptor::execute() {
    std::cout << "start encryption ..." << std::endl;

    for (auto & dir : _dirs) {
        std::vector<boost::filesystem::path> files = _directoryIt->getFilesFromDir(dir);
        //_rsaalgo->encrypt(files);
    }
    std::cout << "SIZE: " << _dirs.size() << std::endl;
}
