#include "Interface/Resource/ResourceNotFound.h"
#include "Interface/Handling/JSONAPI/JsonAPIErrorBuilder.h"

namespace Interface {
namespace Resource {


    void ResourceNotFound::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
        response.setReason(Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);
        response.setContentType("application/vnd.api+json; charset=utf-8");

        Handling::JsonAPIErrorBuilder errorBuilder = Handling::JsonAPIErrorBuilder(request.getHost());

        errorBuilder.withStatusCode(404);
        errorBuilder.sourceAt(request.getURI());
        errorBuilder.withDetails("This route does not exist.");
        errorBuilder.withType(Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND);

        std::ostream & outputStream = response.send();
        outputStream << errorBuilder.build().toString();

        outputStream.flush();

    }


} }
