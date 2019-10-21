#include "Adapter/Validator/HttpContentTypeHeaders.h"

namespace Validator {


    AcceptedHttpContentTypeHeaders::AcceptedHttpContentTypeHeaders(Poco::Net::HTTPRequest & request)
        : _request(request),
          HTTP_CONTENT_TYPE("application/vnd.api+json")
    {}

    bool AcceptedHttpContentTypeHeaders::valid()
    {
        return _request.getContentType() == HTTP_CONTENT_TYPE;
    }

    std::string AcceptedHttpContentTypeHeaders::message() const
    {
        return "The application only supports " + HTTP_CONTENT_TYPE + " as Content Type.";
    }


}
