#include "Adapter/Validator/HttpContentType.h"

namespace Validator {


    HttpContentType::HttpContentType(Poco::Net::HTTPRequest & request)
        : _request(request),
          HTTP_CONTENT_TYPE("application/vnd.api+json")
    {}

    bool HttpContentType::valid()
    {
        return _request.getContentType() == HTTP_CONTENT_TYPE;
    }

    std::string HttpContentType::message() const
    {
        return "The application only supports " + HTTP_CONTENT_TYPE + " as Content Type.";
    }


}
