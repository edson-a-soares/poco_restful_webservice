#include "Poco/StreamCopier.h"
#include "Interface/Resource/Poll/Vote.h"

namespace Interface {
namespace Resource {
namespace Poll {


    Vote::Vote()
        : AbstractResource()
    { }

    Vote::~Vote()
    {
        delete pollApplicationService;
    }

    void Vote::setApplicationService(Application::IPollService * service)
    {
        pollApplicationService = service;
    }

    void Vote::handle_get(Poco::Net::HTTPServerRequest & request,
                          Poco::Net::HTTPServerResponse & response)
    {

        try {

            std::string questionIdentity = getQueryParameter("question_id");
            auto pollResult = pollApplicationService->requestResult(questionIdentity);

            handleHttpStatusCode(200, response);
            std::ostream & outputStream = response.send();

            entityAssembler.setURI(request.getURI());
            entityAssembler.setHost(request.getHost());
            outputStream << entityAssembler.toJson(pollResult);
            outputStream.flush();

        } catch (Resource::Exception & exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream & outputStream = response.send();
            outputStream << toJson(exception);
            outputStream.flush();

        }

    }

    void Vote::handle_post(Poco::Net::HTTPServerRequest & request,
                           Poco::Net::HTTPServerResponse & response)
    {

        try {

            std::string jsonPayload;
            std::istream & inputStream = request.stream();
            Poco::StreamCopier::copyToString(inputStream, jsonPayload);

            auto attributesSectionObject = getJsonAttributesSectionObject(jsonPayload);

            std::list<std::string> attributesNames = { "option_id" };
            assertPayloadAttributes(attributesSectionObject, attributesNames);

            std::string questionIdentity = getQueryParameter("question_id");
            std::string optionIdentity = attributesSectionObject->getValue<std::string>("option_id");
            pollApplicationService->voteOn(questionIdentity, optionIdentity);

            handleHttpStatusCode(204, response);
            std::ostream & outputStream = response.send();
            outputStream.flush();

        } catch (Resource::Exception & exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream & outputStream = response.send();
            outputStream << toJson(exception);
            outputStream.flush();

        }

    }

    void Vote::handle_options(Poco::Net::HTTPServerRequest &,
                              Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "POST, GET, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/plain; charset=utf-8");

        std::ostream& outputStream = response.send();
        outputStream.flush();
    }


} } }
