
#include "httpResponse.h"

namespace butterfly
{

HTTPResponse::HTTPResponse() : HTTPSchema()
{

}

void HTTPResponse::setStatusCode(size_t statusCode)
{
    _statusCode = statusCode;
}

void HTTPResponse::setReasonPhrase(size_t statusCode)
{
    switch(statusCode)
    {
        case 200:
            _reasonPhrase = "";
    }
}

int HTTPResponse::parse()
{
    return 0;
}

void HTTPResponse::prepare()
{

}

} // namespace butterfly
