
#include "httpSchema.h"

namespace butterfly
{

HTTPSchema::HTTPSchema() : _httpMethod(NOT_IMPLEMENTED), _protocol(HTTP_UNSUPPORTED)
{

}

void HTTPSchema::print() const
{
    std::cout << "---HTTP Begin---" << std::endl << _data << "---HTTP End---" << std::endl;
}

void HTTPSchema::addData(const std::string &data)
{
    _data.append(data);
};

void HTTPSchema::setProtocol(Protocol protocol)
{
    _protocol = protocol;
}

void HTTPSchema::addBody(const std::string &body)
{
    _body.append(body);
}

void HTTPSchema::setHTTPHeader(const std::string &headerName, const std::string &headerContent)
{
    _httpHeaders.emplace_back(headerName, headerContent);
}

std::string HTTPSchema::getHTTPHeader(const std::string &headerName) const
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
