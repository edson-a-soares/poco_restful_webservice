#include "Interface/Resource/AbstractResource.h"
#include "Interface/Handling/ErrorJSONParser.h"

namespace Interface {
namespace Resource {


    AbstractResource::AbstractResource()
    { }

    AbstractResource::~AbstractResource()
    { }

    void AbstractResource::handleHTTPHeaders(Poco::Net::HTTPServerRequest & request,
                                             Poco::Net::HTTPServerResponse & response)
    {

        response.setContentType("application/vnd.api+json; charset=utf-8");
        if (request.getContentType() != "application/vnd.api+json" ||
            request.get("Accept") != "application/vnd.api+json"
        ) {
            throw Poco::Exception("Unsupported Media Type",
                "The only media type supported is application/vnd.api+json.", 415);
        }

        if (request.getMethod() !=  Poco::Net::HTTPRequest::HTTP_GET    &&
            request.getMethod() !=  Poco::Net::HTTPRequest::HTTP_PUT    &&
            request.getMethod() !=  Poco::Net::HTTPRequest::HTTP_POST   &&
            request.getMethod() !=  Poco::Net::HTTPRequest::HTTP_DELETE &&
            request.getMethod() !=  Poco::Net::HTTPRequest::HTTP_OPTIONS
        ) {
            throw Poco::Exception("Not Implemented",
                "The request method is not supported by the server and cannot be handled.", 501);
        }

    }

    void AbstractResource::handleRequest(Poco::Net::HTTPServerRequest & request,
                                         Poco::Net::HTTPServerResponse & response) {

        try {
            handleHTTPHeaders(request, response);
        } catch (Poco::Exception & exception) {

            switch (exception.code()) {

                case 415:
                    response.setStatusAndReason(
                        Poco::Net::HTTPResponse::HTTP_UNSUPPORTEDMEDIATYPE,
                        Poco::Net::HTTPResponse::HTTP_REASON_UNSUPPORTEDMEDIATYPE
                    );
                    break;

                case 501:
                    response.setStatusAndReason(
                        Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
                        Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
                    );
                    break;

            }

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

        if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT ) {
            this->handle_put(request, response);
        }

        if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST ) {
            this->handle_post(request, response);
        }

        if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_DELETE ) {
            this->handle_delete(request, response);
        }

        if ( request.getMethod() == Poco::Net::HTTPRequest::HTTP_OPTIONS ) {
            this->handle_options(request, response);
        }

    }

    void AbstractResource::handle_get(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream & errorStream = response.send();
        errorStream.flush();

    }

    void AbstractResource::handle_put(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream & errorStream = response.send();
        errorStream.flush();


    }

    void AbstractResource::handle_post(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream & errorStream = response.send();
        errorStream.flush();

    }

    void AbstractResource::handle_delete(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream & errorStream = response.send();
        errorStream.flush();

    }

    void AbstractResource::handle_options(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatusAndReason(
            Poco::Net::HTTPResponse::HTTP_NOT_IMPLEMENTED,
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_IMPLEMENTED
        );

        std::ostream & errorStream = response.send();
        errorStream.flush();

    }


} }
