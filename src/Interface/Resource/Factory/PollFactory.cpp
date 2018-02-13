#include "Interface/Resource/Poll/Poll.h"
#include "Interface/Resource/Factory/PollFactory.h"
#include "Application/Factory/PollServiceFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {


    Poco::Net::HTTPRequestHandler * PollFactory::createResource()
    {
        auto resource = new Resource::Poll::Poll();
        resource->setApplicationService(
            Application::PollServiceFactory::createService()
        );

        Interface::Handling::QuestionAssembler assembler;
        resource->setEntityAssembler(assembler);

        return resource;
    }


} } }
