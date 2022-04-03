#include <iostream>
#include <memory>

#include "argumentParser.h"

#include "httpRequest.h"
#include "httpResponse.h"

void request()
{
    std::unique_ptr<tools::HTTPRequest> httpRequest = std::unique_ptr<tools::HTTPRequest>(new tools::HTTPRequest());

    std::string url = "localhost:8080";
    httpRequest->setURL(url);
    httpRequest->setMethod(tools::Method::POST);
    httpRequest->setProtocol(tools::Protocol::HTTP1_1);
    httpRequest->setUserAgent("testuser");
    httpRequest->setHTTPHeader("Content-Type", "application/x-www-form-urlencoded");
    httpRequest->setFormParam("form1", "value1");
    httpRequest->setFormParam("form2", "value2");
    httpRequest->addBody(httpRequest->getFormParam());
    httpRequest->setHTTPHeader("Content-Length", std::to_string(httpRequest->getBodyLength()));
    httpRequest->prepareOutgoing();

    httpRequest->print();

}
int main(int argc, char* argv[])
{

    std::unique_ptr<tools::ArgumentParser> argparse = std::unique_ptr<tools::ArgumentParser>(new tools::ArgumentParser(argc, argv));
    tools::ArgumentParser::Arguments args = argparse->parseArgs();

    std::unique_ptr<tools::HTTPResponse> httpResponse = std::unique_ptr<tools::HTTPResponse>(new tools::HTTPResponse());

    httpResponse->setProtocol(tools::Protocol::HTTP1_1);
    httpResponse->setStatusCode(200);
    httpResponse->setReasonPhrase(httpResponse->getStatusCode());
    httpResponse->setHTTPHeader("Connection", "Keep-Alive");
    httpResponse->setHTTPHeader("Content-Type", "text/html; charset=utf8");
    httpResponse->addBody("<!DOCTYPE html><html><body><h1>Test Message</h1></body></html>");
    httpResponse->setHTTPHeader("Content-Length", std::to_string(httpResponse->getBodyLength()));
    httpResponse->prepareOutgoing();

    httpResponse->print();

    return 0;
}

