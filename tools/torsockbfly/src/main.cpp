#include <iostream>
#include <memory>

#include "argumentParser.h"
#include "torSocket.h"
#include "tcpSocket.h"
#include "httpClient.h"

int main(int argc, char *argv[])
{

    std::unique_ptr<tools::ArgumentParser> argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = argparse->parseArgs();

    //std::unique_ptr<tools::TORSocket> torSocket = std::unique_ptr<tools::TORSocket>(new tools::TORSocket(args.client, args.port));
    //std::string response = torSocket->get(args.url);

    //std::unique_ptr<tools::HTTPClient> httpClient = std::unique_ptr<tools::HTTPClient>(new tools::HTTPClient("127.0.0.1", 9050));
    //std::string response = httpClient->get("127.0.0.1", 5000);
    //std::string response = httpClient->getTor("y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion", 80);
    //std::cout << "Response: \n" << response << std::endl;

    //std::shared_ptr<tools::TCPSocket> tcpSocket = std::make_shared<tools::TCPSocket>();
    std::shared_ptr<tools::TORSocket> torSocket = std::make_shared<tools::TORSocket>("127.0.0.1", 9050);
    std::unique_ptr<tools::HTTPClient> httpClient = std::unique_ptr<tools::HTTPClient>(new tools::HTTPClient(torSocket));
    //std::string response = httpClient->get("127.0.0.1", 5000);
    std::string response = httpClient->get("http://y55reqejevhbvyrl6r3yahz5ctsrz7v4glkrcklvyso4a3whht3lhfyd.onion/", 80);

    //std::string response = httpClient->post("http://localhost:5000/api/v1/decryption/", "test", 5000);
    std::cout << "Response: \n" << response << std::endl;

    return 0;
}

