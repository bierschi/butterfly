#include <iostream>
#include <memory>

#include "argumentParser.h"
#include "tcpSocket.h"

void serversocket(int port)
{
    std::shared_ptr<tools::TCPSocket> serverSocket = std::make_shared<tools::TCPSocket>();
    serverSocket->bind(port);
    serverSocket->listen();
    std::cout << "ServerSocket listens for incoming connections on port " << port << std::endl;
    std::shared_ptr<tools::TCPSocket> newSocket = serverSocket->accept();

    std::string s = newSocket->recvAll(1024, true);

    std::cout << "Recv: " << s << std::endl;


    serverSocket->disconnect();
}

void clientsocket(const std::string &ip, int port)
{
    std::shared_ptr<tools::TCPSocket> clientSocket = std::make_shared<tools::TCPSocket>();
    if ( clientSocket->connect(ip, port) )
    {
        std::cout << "ClientSocket connected to " << ip << " on port " << port << std::endl;

        clientSocket->send("Message to server");

        clientSocket->disconnect();
    } else
    {
        std::cerr << "Could not connect to " << ip << " on port " << port << std::endl;
    }

}

int main(int argc, char* argv[])
{

    std::unique_ptr<tools::ArgumentParser> argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = argparse->parseArgs();

    if ( args.server )
    {

        serversocket( args.port );

    } else if ( args.client )
    {
        clientsocket( args.ip, args.port );
    }

    return 0;
}
