#include "Poco/URI.h"
#include "Adapter/Http/ErrorJsonAPIParser.h"
#include "Adapter/Http/DefaultNotFoundErrorHandler.h"

namespace Http {


	void DefaultNotFoundErrorHandler::handleRequest(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
	{
        response.setContentType("application/vnd.api+json");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);

        std::string errorMessage;
        ::Http::ErrorJsonAPIParser errorParser;
        Poco::URI uri = Poco::URI(request.getURI());

        errorMessage = errorParser.toJson(
            request.getHost(),
            "404",
            uri.getPath(),
            Poco::Net::HTTPResponse::HTTP_REASON_NOT_FOUND,
            "This endpoint does not exist."
        );

        response.sendBuffer(errorMessage.data(), errorMessage.length());
	}


}
