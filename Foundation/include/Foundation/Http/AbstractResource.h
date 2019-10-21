#ifndef Foundation_Http_AbstractResource_INCLUDED
#define Foundation_Http_AbstractResource_INCLUDED

#include <memory>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Foundation/Http/ErrorParserInterface.h"
#include "Foundation/Http/CORSHeadersInterface.h"

namespace Foundation {
namespace Http {


    class AbstractResource : public Poco::Net::HTTPRequestHandler
    {
    public:
        ~AbstractResource() override = default;
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    protected:
        static std::map<std::string, std::string> corsHeaders();
        virtual std::unique_ptr<ErrorParserInterface> errorParser();

        virtual void handle_get(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_put(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_patch(  Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_delete( Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

    private:
        static void corsHeaders(Poco::Net::HTTPServerResponse &);

    };


} }

#endif
