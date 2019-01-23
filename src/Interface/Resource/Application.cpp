#include "Interface/Resource/Application.h"

namespace Interface {
namespace Resource {


    Application::Application()
        : AbstractResource()
    { }

    void Application::handle_get(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        std::ostream & outputStream = response.send();
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

        Handling::JsonAPIResourceBuilder resourceBuilder(request.getHost());

        resourceBuilder.linkTo("polls_url",        "/polls?question_id={id}");
        resourceBuilder.linkTo("polls_vote_url",   "/polls/votes");
        resourceBuilder.linkTo("polls_result_url", "/polls/votes?question_id={id}");

        Poco::Dynamic::Array langs;
        langs.emplace_back("en-US");

        resourceBuilder.withMetadata("langs", langs);
        resourceBuilder.withMetadata("jsonapi", "1.1");
        resourceBuilder.withMetadata("copyright", "Copyright 2018 Poco RESTful WebService");

        outputStream << resourceBuilder.build().toString();
        outputStream.flush();

    }

    void Application::handle_options(Poco::Net::HTTPServerRequest &,
                                     Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "GET, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/plain; charset=utf-8");

        std::ostream& outputStream = response.send();
        outputStream.flush();
    }


} }
