#ifndef Validation_AllowedHttpMethods_INCLUDED
#define Validation_AllowedHttpMethods_INCLUDED

#include "Poco/Net/HTTPRequest.h"
#include "Foundation/Validator/ValidatorInterface.h"

namespace Validator {


    class HttpMethods : public Foundation::Validator::ValidatorInterface
    {
    public:
        explicit HttpMethods(Poco::Net::HTTPRequest &);
        bool valid() override;
        std::string message() const override;

    private:
        Poco::Net::HTTPRequest & _request;

    };


}

#endif
