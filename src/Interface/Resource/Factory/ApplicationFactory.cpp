#include "Interface/Resource/Application.h"
#include "Interface/Resource/Factory/ApplicationFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {


    Poco::Net::HTTPRequestHandler * ApplicationFactory::createResource()
    {
        return new Resource::Application();
    }


} } }
