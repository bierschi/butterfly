
#include "butterfly.h"

#include "tcpSocket.h"
namespace butterfly
{

Butterfly::Butterfly(int argc, char *argv[]) : _argparse(new butterfly::ArgumentParser())
{

    // parse args with the argument parser
    _args = _argparse->parseArgs(argc, argv);

    LOG_INFO("Running " << PROJECT_NAME << " with version " << _args._version);
    std::cout << "Running " << PROJECT_NAME << " with version " << _args._version << std::endl;
}

void Butterfly::run()
{
    std::shared_ptr<butterfly::TCPSocket> _serverSocket = std::make_shared<butterfly::TCPSocket>();
    _serverSocket->bind(8080);
    _serverSocket->listen();
    std::shared_ptr<butterfly::TCPSocket> newSocket = _serverSocket->accept();

    std::string body = "<!DOCTYPE html><html><body>TEST MeSSAGE</body></html>";
    std::string test = "HTTP/1.1 302 Found \r\nContent-Type: text/html; charset=utf8 \r\nContent-Length:" + std::to_string(body.length()) + "\r\n\r\n" + body;

    //newSocket->send("HTTP/1.1 302 Found \r\nContent-Type: text/html; charset=utf8 \r\nContent-Length:279\r\n\r\n<!DOCTYPE html><html><head><title>Creating an HTML Element</title></head><body><form name=\"input\" action=\"login.html\" method=\"get\">user name: <input type=\"text\" name=\"user\"><br>password: <input type=\"text\" name=\"password\"><input type=\"submit\" value=\"Submit\"></form></body></html>");
    newSocket->send(test);

    std::string s;
    newSocket->recv(s, 1024);
    std::cout << s << std::endl;
    newSocket->recv(s, 1024);
    std::cout << s << std::endl;
    /*
    // Start Encryption + Decryption
    if ( !_args._dir.empty() )
    {
        // start encryption
        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption+Decryption from directory " << _args._dir << std::endl;
        encryptor->invokeDir(_args._dir, _args._protected);

        sleep(5);

        // start decryption
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        decryptor->invokeDir(_args._dir, "/home/christian/projects/butterfly/masterkeys/SPrivateRSA.pem");

    }
        // Start only Encryption
    else if ( !_args._encrypt.empty() )
    {

        std::unique_ptr<butterfly::hybrid::Encryptor> encryptor(new butterfly::hybrid::Encryptor(2048));
        std::cout << "Start Encryption from directory " << _args._encrypt << std::endl;
        encryptor->invokeDir(_args._encrypt, _args._protected);

    }
        // Start only Decryption
    else if ( !_args._decrypt.empty() )
    {
        std::unique_ptr<butterfly::hybrid::Decryptor> decryptor(new butterfly::hybrid::Decryptor());
        std::cout << "Start Decryption from directory " << _args._decrypt << std::endl;
        decryptor->invokeDir(_args._decrypt, _args._serverpKey);
    } else
    {
        throw ButterflyException("Invalid usage of the Arguments!");
    }
     */
}

} // namespace butterfly
