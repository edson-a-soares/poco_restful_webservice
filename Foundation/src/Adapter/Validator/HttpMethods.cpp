#include "Adapter/Validator/HttpMethods.h"

namespace Validator {


    HttpMethods::HttpMethods(Poco::Net::HTTPRequest & request)
        : _request(request)
    {}

    bool HttpMethods::valid()
    {
        return _request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET     ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST    ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT     ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE  ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_PATCH   ||
               _request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS;
    }

    std::string HttpMethods::message() const
    {
        return "The requested application resource does not support this specific http method.";
    }


}
