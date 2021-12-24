
#include <memory>

#include "aes.h"

int main (int argc, char* argv[])
{

    std::unique_ptr<tools::CryptoAES> cryptoAES(new tools::CryptoAES());


    return 0;
}