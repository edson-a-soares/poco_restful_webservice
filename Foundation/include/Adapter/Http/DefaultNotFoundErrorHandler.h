#ifndef Http_DefaultNotFoundErrorHandler_INCLUDED
#define Http_DefaultNotFoundErrorHandler_INCLUDED

#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"

namespace Http {


    class DefaultNotFoundErrorHandler : public Poco::Net::HTTPRequestHandler
    {
    public:
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


}

#endif
