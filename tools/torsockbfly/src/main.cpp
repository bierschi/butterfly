#include <iostream>
#include <memory>

#include "argumentParser.h"
#include "torSocket.h"

int main(int argc, char *argv[])
{

    std::unique_ptr<tools::ArgumentParser> argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = argparse->parseArgs();

    std::unique_ptr<tools::TORSocket> torSocket = std::unique_ptr<tools::TORSocket>(new tools::TORSocket(args.client, args.port));
    std::string response = torSocket->get(args.url);

    std::cout << "Response: \n" << response << std::endl;

    return 0;
}

