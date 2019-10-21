#ifndef Validator_HttpContentTypeHeaders_INCLUDED
#define Validator_HttpContentTypeHeaders_INCLUDED

#include "Poco/Net/HTTPRequest.h"
#include "Foundation/Validator/ValidatorInterface.h"

namespace Validator {


    class AcceptedHttpContentTypeHeaders : public Foundation::Validator::ValidatorInterface
    {
    public:
        explicit AcceptedHttpContentTypeHeaders(Poco::Net::HTTPRequest &);
        bool valid() override;
        std::string message() const override;

    private:
        Poco::Net::HTTPRequest & _request;
        const std::string HTTP_CONTENT_TYPE;

    };


}

#endif
