#include "Poco/Net/HTTPResponse.h"
#include "Interface/Resource/Exception.h"
#include "Interface/Handling/Assembler/QuestionAssembler.h"
#include "Interface/Handling/JSONAPI/JsonAPIResourceCollectionBuilder.h"

namespace Interface {
namespace Handling {


    QuestionAssembler::QuestionAssembler()
        : URI(),
          host()
    { }


    void QuestionAssembler::setHost(const std::string & _host)
    {
        host = _host;
    }

    void QuestionAssembler::setURI(const std::string & address)
    {
        URI = address;
    }

    std::string QuestionAssembler::toJson(const Domain::Model::Poll::Question & question)
    {

        std::string jsonData;
        auto * rootResourceBuilder = new Interface::Handling::JsonAPIResourceBuilder();

        try {

            rootResourceBuilder->withType("questions");
            rootResourceBuilder->hostedAt(host);
            rootResourceBuilder->withIdentity(question.identity());

            rootResourceBuilder->addAttribute("text", question.text());
            rootResourceBuilder->addAttribute("label", question.label());
            rootResourceBuilder->addAttribute("details", question.details());
            rootResourceBuilder->addAttribute("ends_at", question.endAt());
            rootResourceBuilder->addAttribute("starts_at", question.startAt());
            rootResourceBuilder->addAttribute("created_at", question.createdAt());
            rootResourceBuilder->addAttribute("last_updated_at", question.lastUpdatedAt());

            rootResourceBuilder->linkTo("self", URI);

            auto optionsList = question.options();
            for ( auto const & option : optionsList ) {

                auto * includedResourceBuilder = new Interface::Handling::JsonAPIResourceBuilder();

                includedResourceBuilder->withType("question_options");
                includedResourceBuilder->withIdentity(option.identity());

                includedResourceBuilder->addAttribute("text", option.text());
                includedResourceBuilder->addAttribute("position", option.positionedAt());
                includedResourceBuilder->addAttribute("created_at", option.createdAt());
                includedResourceBuilder->addAttribute("last_updated_at", option.lastUpdatedAt());

                rootResourceBuilder->addIncludeResource(includedResourceBuilder);
                delete includedResourceBuilder;

            }

            jsonData = rootResourceBuilder->build().toString();

        } catch (Poco::Exception & exception) {
            exception.rethrow();
        }

        delete rootResourceBuilder;
        return jsonData;

    }

    std::string QuestionAssembler::toJson(const std::list<Application::PollResult> & pollResults)
    {

        std::string jsonData;
        auto * resourceCollectionBuilder = new Interface::Handling::JsonAPIResourceCollectionBuilder();

        try {

            for ( auto const & result : pollResults ) {

                auto * resourceBuilder = new Interface::Handling::JsonAPIResourceBuilder();

                resourceBuilder->withType("question_votes");
                resourceBuilder->addAttribute("option_id", result.first);

                resourceBuilder->hostedAt(host);
                resourceBuilder->linkTo("self", URI);
                resourceBuilder->withMetadata("count", std::to_string(result.second));

                resourceCollectionBuilder->addResource(resourceBuilder);
                delete resourceBuilder;

            }

            jsonData = resourceCollectionBuilder->build().toString();

        } catch (Poco::Exception & exception) {
            exception.rethrow();
        }

        delete resourceCollectionBuilder;
        return jsonData;

    }

    Domain::Model::Poll::Question QuestionAssembler::assembleEntity(const Poco::JSON::Object::Ptr & attributesObject)
    {

        Domain::Model::Poll::Question newQuestion;
        try {

            auto optionsList = assembleOptionsList(attributesObject);
            for ( auto & option : optionsList )
                newQuestion.add(option);

            int timeZoneDifference = 0;
            auto startDate = Poco::DateTimeParser::parse(
                Poco::DateTimeFormat::SORTABLE_FORMAT,
                attributesObject->getValue<std::string>("starts_at"),
                timeZoneDifference
            );
            newQuestion.startAt(startDate);

            auto endsDate = Poco::DateTimeParser::parse(
                Poco::DateTimeFormat::SORTABLE_FORMAT,
                attributesObject->getValue<std::string>("ends_at"),
                timeZoneDifference
            );
            newQuestion.endAt(endsDate);

            newQuestion.withText(attributesObject->getValue<std::string>("text"));
            newQuestion.withLabel(attributesObject->getValue<std::string>("label"));
            newQuestion.withDetails(attributesObject->getValue<std::string>("details"));

        } catch (Poco::Exception & exception) {
            exception.rethrow();
        }

        return newQuestion;

    }

    std::list<Domain::Model::Poll::Option> QuestionAssembler::assembleOptionsList(const Poco::JSON::Object::Ptr & jsonObject)
    {

        std::list<Domain::Model::Poll::Option> options;
        try {
            // Validating the section 'options'
            if ( !jsonObject->isArray("options") ) {
                throw Resource::Exception(
                    Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                    "A list of 'options' is missing at the payload.",
                    Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
                );
            }

            auto jsonOptionsArray = jsonObject->getArray("options");
            std::size_t jsonOptionsArraySize = jsonOptionsArray->size();

            if ( jsonOptionsArraySize < 2 ) {
                throw Resource::Exception(
                    Poco::Net::HTTPResponse::HTTP_REASON_BAD_REQUEST,
                    "A Question can not be created without at least two options.",
                    Poco::Net::HTTPResponse::HTTP_BAD_REQUEST
                );
            }

            for ( unsigned int i = 0; i < jsonOptionsArraySize; ++i ) {

                auto optionObject = jsonOptionsArray->getObject(i);

                Domain::Model::Poll::Option option;
                option.withText(optionObject->getValue<std::string>("text"));
                options.push_back(option);

            }

        } catch (Resource::Exception & exception) {
            throw exception;
        }

        return options;

    }


} }
