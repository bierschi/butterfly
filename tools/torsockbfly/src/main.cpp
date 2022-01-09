#include <iostream>
#include <memory>

#include "torSocket.h"

int main(int argc, char *argv[])
{

    std::unique_ptr<tools::TORSocket> torSocket = std::unique_ptr<tools::TORSocket>(new tools::TORSocket("127.0.0.1", 9050));
    std::string s = torSocket->request("icanhazip.com", 80);

    std::cout << "Response: " << s << std::endl;
    return 0;
}

