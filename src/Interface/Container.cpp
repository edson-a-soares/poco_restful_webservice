#include <iostream>
#include "Poco/String.h"
#include "Interface/Container.h"
#include "Poco/Net/HTTPServer.h"

namespace Interface {


    Container::Container()
        : port(9000),
          endpoint("localhost")
    { }

    Container::~Container()
    {
        delete router;
    }

    int Container::main(const std::vector<std::string> &)
    {

        auto * httpServerParams = new Poco::Net::HTTPServerParams();

        httpServerParams->setMaxQueued(250);
        httpServerParams->setMaxThreads(50);

        Poco::Net::HTTPServer httpServer(getRouter(), Poco::Net::ServerSocket(Poco::UInt16(port)), httpServerParams);

        std::cout << "Poco Restful Web Service started and running." << std::endl;
        std::cout << "Type http://" << endpoint << ":" << port << " to use it or ";
        std::cout << "type CRLT+C to finish it." << std::endl;

        httpServer.start();
        waitForTerminationRequest();
        httpServer.stop();

        std::cout << "\nPoco Restful Web Service stopped. \nGoodbye." << std::endl;
        return Poco::Util::Application::EXIT_OK;

    }

    void Container::setPort(int _port)
    {
        port = _port;
    }

    void Container::setRouter(Poco::Net::HTTPRequestHandlerFactory * _router)
    {
        router = _router;
    }

    Poco::Net::HTTPRequestHandlerFactory * Container::getRouter()
    {
        return router;
    }


}
