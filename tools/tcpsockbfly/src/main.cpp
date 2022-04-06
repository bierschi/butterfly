#include <iostream>
#include <memory>

#include "argumentParser.h"
#include "tcpSocket.h"

#define BUFSIZE 1024

void serversocket(int port)
{
    std::shared_ptr<tools::TCPSocket> serverSocket = std::make_shared<tools::TCPSocket>();
    serverSocket->bind(port);
    serverSocket->listen();
    std::cout << "ServerSocket listens for incoming connections on port " << port << "..." << std::endl;

    std::shared_ptr<tools::TCPSocket> newSocket = serverSocket->accept();
    std::cout << "Connected with client!" << std::endl;

    char msg[BUFSIZE];
    while(true)
    {

        std::cout << "Awaiting client response..." << std::endl;

        newSocket->recv(msg, BUFSIZE);
        if(!strcmp(msg, "exit"))
        {
            std::cout << "Client has quit the session" << std::endl;
            break;
        }

        std::cout << "Client: " << msg << std::endl;
        std::cout << ">";
        std::string data;
        std::getline(std::cin, data);

        strcpy(msg, data.c_str());
        if(data == "exit")
        {
            newSocket->send(msg);
            break;
        }

        newSocket->send(msg);
    }

    serverSocket->disconnect();
}

void clientsocket(const std::string &ip, int port)
{
    std::shared_ptr<tools::TCPSocket> clientSocket = std::make_shared<tools::TCPSocket>();
    if ( clientSocket->connect(ip, port) )
    {
        std::cout << "ClientSocket connected to " << ip << " on port " << port << std::endl;
        char msg[BUFSIZE];

        while (true)
        {

            std::string data;
            std::cout << "> ";
            std::getline(std::cin, data);

            strcpy(msg, data.c_str());
            if(data == "exit")
            {
                clientSocket->send(msg);
                break;
            }
            clientSocket->send(msg);
            std::cout << "Awaiting server response..." << std::endl;

            clientSocket->recv(msg, BUFSIZE);
            if(!strcmp(msg, "exit"))
            {
                std::cout << "Server has quit the session" << std::endl;
                break;
            }
            std::cout << "Server: " << msg << std::endl;

        }

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
