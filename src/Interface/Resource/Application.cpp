#include "Interface/Resource/Application.h"
#include "Interface/Handling/ApplicationJSONParser.h"

namespace Interface {
namespace Resource {


    Application::Application()
        : AbstractResource()
    { }

    Application::~Application()
    { }

    void Application::handle_get(Poco::Net::HTTPServerRequest & request, Poco::Net::HTTPServerResponse & response)
    {

        std::ostream & outputStream = response.send();
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        Handling::ApplicationJSONParser parser = Handling::ApplicationJSONParser(request.getHost());

        outputStream << parser.toJson("1.0");
        outputStream.flush();

    }

    void Application::handle_options(Poco::Net::HTTPServerRequest & request,
                                 Poco::Net::HTTPServerResponse & response)
    {
        response.set("Allow", "GET, OPTIONS");
        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
        response.setContentType("text/plain; charset=utf-8");

        std::ostream& outputStream = response.send();
        outputStream.flush();
    }


} }
