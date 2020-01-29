//
// Created on 28.01.20.
//

#ifndef RANSOMWARE_ALGORITHM_H
#define RANSOMWARE_ALGORITHM_H
#include <boost/filesystem.hpp>

/**
 * Abstract Base Class Algorithm
 */
class Algorithm {

public:
    Algorithm() {};
    virtual ~Algorithm() {};

    virtual void encrypt(std::vector<boost::filesystem::path>&) = 0;
    virtual void decrypt() = 0;

};


#endif //RANSOMWARE_ALGORITHM_H
