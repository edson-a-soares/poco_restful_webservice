#ifndef Foundation_Http_Router_INCLUDED
#define Foundation_Http_Router_INCLUDED

#include <map>
#include <memory>
#include <string>
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Foundation/Http/RouterAbstractFactoryInterface.h"

namespace Foundation {
namespace Http {


    class Router : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        Poco::Net::HTTPRequestHandler * createRequestHandler (const Poco::Net::HTTPServerRequest &) final;

    protected:
        virtual void loadEndpoints() = 0;
        virtual Poco::Net::HTTPRequestHandler * notFoundErrorHandler();
        virtual std::unique_ptr<RouterAbstractFactoryInterface> getAbstractFactory() = 0;
        void addEndpoint(const std::string & path, const std::string & resourceFactoryName);

    private:
        std::map<std::string, std::string> routingTable = {};

        std::string endpointFactoryKey(const std::string & path);

    };


} }

#endif
