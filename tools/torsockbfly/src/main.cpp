#include <iostream>
#include <memory>

#include "torSocket.h"

int main(int argc, char *argv[])
{

    std::unique_ptr<tools::TORSocket> torSocket = std::unique_ptr<tools::TORSocket>(new tools::TORSocket("127.0.0.1", 9050));
    //std::string s = torSocket->request("icanhazip.com", 80);
    //std::string s = torSocket->get("y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion", 80);
    std::string s = torSocket->get("y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion/api/v1/decryption/counter/", 80);
    //std::string s = torSocket->post("y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion/api/v1/decryption", "data", 80);
    std::cout << "Response: " << s << std::endl;
    return 0;
}

