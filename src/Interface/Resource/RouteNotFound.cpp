#include "Interface/Resource/RouteNotFound.h"
#include "Interface/Handling/ErrorJSONParser.h"

namespace Interface {
namespace Resource {


    void RouteNotFound::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        response.setReason(Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
        response.setContentType("application/vnd.api+json; charset=utf-8");

        Handling::ErrorJSONParser error = Handling::ErrorJSONParser(request.getHost());

        std::ostream & outputStream = response.send();
        outputStream << error.toJson(404, request.getURI(),
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND, "This route does not exist."
        );

        outputStream.flush();

    }


} }
