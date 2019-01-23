#include "Interface/Resource/Poll/Poll.h"
#include "Poco/StreamCopier.h"
#include "Poco/JSON/Parser.h"

namespace Interface {
namespace Resource {
namespace Poll {


    Poll::Poll()
        : AbstractResource()
    { }

    Poll::~Poll()
    {
        delete pollApplicationService;
    }

    void Poll::setApplicationService(Application::IPollService * service)
    {
        pollApplicationService = service;
    }

    void Poll::setEntityAssembler(Interface::Handling::QuestionAssembler & assembler)
    {
        entityAssembler = assembler;
    }

    void Poll::handle_get(Poco::Net::HTTPServerRequest & request,
                          Poco::Net::HTTPServerResponse & response)
    {

        try {

            std::string questionIdentity = getQueryParameter("question_id");
            auto foundQuestion = pollApplicationService->findQuestion(questionIdentity);

            handleHttpStatusCode(200, response);
            std::ostream & outputStream = response.send();

            entityAssembler.setURI(request.getURI());
            entityAssembler.setHost(request.getHost());
            outputStream << entityAssembler.toJson(foundQuestion);
            outputStream.flush();

        } catch (Resource::Exception & exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream & outputStream = response.send();
            outputStream << toJson(exception);

        }

    }

    void Poll::handle_put(Poco::Net::HTTPServerRequest & request,
                          Poco::Net::HTTPServerResponse & response)
    {

        try {

            std::string jsonPayload;
            std::istream & inputStream = request.stream();
            Poco::StreamCopier::copyToString(inputStream, jsonPayload);

            auto attributesSectionObject = getJsonAttributesSectionObject(jsonPayload);

            std::list<std::string> attributesNames = { "starts_at", "ends_at", "details", "label", "text" };
            assertPayloadAttributes(attributesSectionObject, attributesNames);

            auto assembledQuestion = entityAssembler.assembleEntity(attributesSectionObject);
            pollApplicationService->changeQuestion(assembledQuestion);

            handleHttpStatusCode(200, response);
            std::ostream & outputStream = response.send();
            outputStream.flush();

        } catch (Resource::Exception & exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream & outputStream = response.send();
            outputStream << toJson(exception);
            outputStream.flush();

        }

    }

    void Poll::handle_post(Poco::Net::HTTPServerRequest & request,
                           Poco::Net::HTTPServerResponse & response)
    {

        try {

            std::string jsonPayload;
            std::istream & inputStream = request.stream();
            Poco::StreamCopier::copyToString(inputStream, jsonPayload);

            auto attributesSectionObject = getJsonAttributesSectionObject(jsonPayload);

            std::list<std::string> attributesNames = { "starts_at", "ends_at", "details", "label", "text", "options" };
            assertPayloadAttributes(attributesSectionObject, attributesNames);

            auto assembledQuestion = entityAssembler.assembleEntity(attributesSectionObject);
            std::string newQuestionIdentity = pollApplicationService->newQuestion(assembledQuestion);

            response.set("Location", getUrl("?question_id=" + newQuestionIdentity));
            response.set("Content-Location", getUrl("?question_id=" + newQuestionIdentity));

            handleHttpStatusCode(201, response);
            std::ostream & outputStream = response.send();
            outputStream.flush();

        } catch (Resource::Exception & exception) {

            handleHttpStatusCode(exception.code(), response);
            std::ostream & outputStream = response.send();
            outputStream << toJson(exception);
            outputStream.flush();

        }

    }

    void Poll::handle_delete(Poco::Net::HTTPServerRequest &,
                             Poco::Net::HTTPServerResponse & response)
    {

        try {

            std::string questionIdentity = getQueryParameter("question_id");
            pollApplicationService->eraseQuestion(questionIdentity);

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

    void Poll::handle_options(Poco::Net::HTTPServerRequest &,
                              Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "GET, PUT, POST, DELETE, OPTIONS");
        response.setContentType("text/plain; charset=utf-8");

        handleHttpStatusCode(200, response);
        std::ostream & outputStream = response.send();
        outputStream.flush();
    }


} } }
