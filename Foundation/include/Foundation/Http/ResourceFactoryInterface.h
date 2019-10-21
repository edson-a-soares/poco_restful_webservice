#ifndef Foundation_Http_ResourceFactoryInterface_INCLUDED
#define Foundation_Http_ResourceFactoryInterface_INCLUDED

#include "Poco/Net/HTTPRequestHandler.h"

namespace Foundation {
namespace Http {


    class ResourceFactoryInterface
    {
    public:
        virtual ~ResourceFactoryInterface() = default;
        virtual Poco::Net::HTTPRequestHandler * createResource() = 0;

    };


} }

#endif
