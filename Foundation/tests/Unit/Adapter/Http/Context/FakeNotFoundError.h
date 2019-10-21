#ifndef UnitTests_Http_Context_FakeNotFoundError_INCLUDED
#define UnitTests_Http_Context_FakeNotFoundError_INCLUDED

#include "Poco/URI.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Adapter/Http/Context/FakeErrorJsonAPIParser.h"

namespace UnitTests {
namespace Http {
namespace Context {


    class FakeNotFoundError : public Poco::Net::HTTPRequestHandler
    {
    public:
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


    void FakeNotFoundError::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {
        response.setContentType("application/vnd.api+json");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);

        std::string errorMessage;
        Poco::URI uri = Poco::URI(request.getURI());
        UnitTests::Http::Context::FakeErrorJSONParser errorParser;

        errorMessage = errorParser.toJson(
            request.getHost(),
            "404",
            uri.getPath(),
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND,
            " This endpoint does not exist."
        );

        response.sendBuffer(errorMessage.data(), errorMessage.length());
    }


} } }

#endif
