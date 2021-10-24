
#include "httpMSGSchema.h"

namespace butterfly
{

HTTPMSGSchema::HTTPMSGSchema(const std::string &messageType) : _messageType(messageType), _httpMethod(NOT_IMPLEMENTED), _protocol(HTTP_UNSUPPORTED)
{

}

void HTTPMSGSchema::print() const
{
    std::cout << "---HTTP " << _messageType << " Begin---" << std::endl << _httpData << "---HTTP " << _messageType << " End---" << std::endl;
}

void HTTPMSGSchema::addHTTPData(const std::string &httpData)
{
    _httpData.append(httpData);
};

void HTTPMSGSchema::setProtocol(Protocol protocol)
{
    _protocol = protocol;
}

void HTTPMSGSchema::addBody(const std::string &body)
{
    _body.append(body);
}

void HTTPMSGSchema::setHTTPHeader(const std::string &headerName, const std::string &headerContent)
{
    _httpHeaders.emplace_back(headerName, headerContent);
}

std::string HTTPMSGSchema::getHTTPHeader(const std::string &headerName) const
{
    for(auto &it: _httpHeaders)
    {
        if(it.first == headerName)
        {
            return it.second;
        }
    }

    return "";
}

} // namespace butterfly
