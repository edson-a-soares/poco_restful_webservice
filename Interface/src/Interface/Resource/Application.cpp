#include "Interface/Resource/Application.h"
#include "Interface/Handling/ErrorJSONParser.h"
#include "Interface/Handling/ApplicationJSONParser.h"

namespace Interface {
namespace Resource {


    Application::Application()
    { }

    void Application::validateHTTPRequiredHeaders(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setContentType("application/vnd.api+json; charset=utf-8");
        if ( request.getContentType() != "application/vnd.api+json" || request.get("Accept") != "application/vnd.api+json" ) {

            response.setStatusAndReason(
                Poco::Net::HTTPResponse::HTTP_UNSUPPORTEDMEDIATYPE,
                Poco::Net::HTTPResponse::HTTP_REASON_UNSUPPORTEDMEDIATYPE
            );

            throw Poco::Exception("Unsupported Media Type",
                "The only media type supported is application/vnd.api+json.", 415);

        }

        if ( request.getMethod() != Poco::Net::HTTPRequest::HTTP_GET ) {

            response.setStatusAndReason(
                Poco::Net::HTTPResponse::HTTP_METHOD_NOT_ALLOWED,
                Poco::Net::HTTPResponse::HTTP_REASON_METHOD_NOT_ALLOWED
            );

            throw Poco::Exception("Method Not Allowed",
                "The requested resource does not support http method.", 405);

        }

    }

    void Application::handleRequest(Poco::Net::HTTPServerRequest & request,
                                    Poco::Net::HTTPServerResponse & response) {

        try {

            validateHTTPRequiredHeaders(request, response);

        } catch ( Poco::Exception & exception ) {

            Handling::ErrorJSONParser error = Handling::ErrorJSONParser(request.getHost());
            std::ostream & errorStream      = response.send();

            errorStream << error.toJson(exception.code(), request.getURI(),
                                exception.what(), exception.message());

            errorStream.flush();
            return;

        }

        if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_GET ) {
            this->handle_get(request, response);
        }

    }

    void Application::handle_get(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        std::ostream & outputStream = response.send();

        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        Handling::ApplicationJSONParser parser = Handling::ApplicationJSONParser(request.getHost());

        outputStream << parser.toJson("1.0");
        outputStream.flush();

    }


} }
