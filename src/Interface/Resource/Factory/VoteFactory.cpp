#include "Interface/Resource/Factory/VoteFactory.h"
#include "Application/Factory/PollServiceFactory.h"
#include "Interface/Resource/Poll/Vote.h"

namespace Interface {
namespace Resource {
namespace Factory {


    Poco::Net::HTTPRequestHandler * VoteFactory::createResource()
    {
        auto resource = new Resource::Poll::Vote();
        resource->setApplicationService(
            Application::PollServiceFactory::createService()
        );

        return resource;
    }


} } }
