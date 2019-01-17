#include "Poco/URI.h"
#include "Interface/Router.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Interface/Resource/ResourceNotFound.h"
#include "Interface/Resource/Factory/Factory.h"

namespace Interface {


    Router::Router()
    {
        init();
    }

    void Router::init()
    {
        addRoute("/polls",       "Interface::Resource::Factory::PollFactory");
        addRoute("/polls/votes", "Interface::Resource::Factory::PollVoteFactory");
        addRoute("/",            "Interface::Resource::Factory::ApplicationFactory");
    }

    Poco::Net::HTTPRequestHandler * Router::createRequestHandler(const Poco::Net::HTTPServerRequest & request)
    {
        return getResource(request.getURI());
    }

    Poco::Net::HTTPRequestHandler * Router::getResource(const std::string & route)
    {

        Poco::URI uri = Poco::URI(route);
        auto factoryIndex = routingTable.find(uri.getPath());
        if ( factoryIndex == routingTable.end() ) {
            return new Interface::Resource::ResourceNotFound();
        }

        Interface::Resource::Factory::IFactory * factory =
            Interface::Resource::Factory::Factory::createResourceFactory(factoryIndex->second);

        return factory->createResource();

    }

    void Router::addRoute(const std::string & route, const std::string & factory)
    {
        routingTable[route] = factory;
    }


}

// add support to Poco ApacheConnector
POCO_BEGIN_MANIFEST(Poco::Net::HTTPRequestHandlerFactory)
        POCO_EXPORT_CLASS(Interface::Router)
POCO_END_MANIFEST