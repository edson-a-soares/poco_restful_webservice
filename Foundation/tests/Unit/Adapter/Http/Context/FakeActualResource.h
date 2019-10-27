#ifndef UnitTests_Http_Context_FakeActualResource_INCLUDED
#define UnitTests_Http_Context_FakeActualResource_INCLUDED

#include <memory>
#include "Foundation/Http/AbstractResource.h"
#include "Foundation/Http/ErrorParserInterface.h"
#include "Adapter/Http/Context/FakeErrorJsonAPIParser.h"

namespace UnitTests {
namespace Http {
namespace Context {


    class FakeActualResource : public Foundation::Http::AbstractResource
    {
    protected:
        std::unique_ptr<Foundation::Http::ErrorParserInterface> errorParser() override;

        void handle_get(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_put(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;
        void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    };


    std::unique_ptr<Foundation::Http::ErrorParserInterface> FakeActualResource::errorParser()
    {
        return std::make_unique<FakeErrorJSONParser>();
    }

    void FakeActualResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & reponse)
    {
        reponse.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        std::ostream & outputStream = reponse.send();
        outputStream << "{}";
        outputStream.flush();
    }

    inline void FakeActualResource::handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
    {
        throw Poco::SyntaxException("Bad Request", "You sent a request that this server could not understand.", 400);
    }

    inline void FakeActualResource::handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        auto resourceLocation = "http://localhost?key=value";

        response.set("Content-Location", resourceLocation);
        response.setStatus(Poco::Net::HTTPResponse::HTTP_CREATED);
    }

    inline void FakeActualResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "GET, POST, PUT, OPTIONS, PATCH");
    }


} } }

#endif
