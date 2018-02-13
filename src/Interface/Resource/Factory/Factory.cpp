#include "Interface/Resource/Factory/Factory.h"
#include "Interface/Resource/Factory/VoteFactory.h"
#include "Interface/Resource/Factory/PollFactory.h"
#include "Interface/Resource/Factory/ApplicationFactory.h"

namespace Interface {
namespace Resource {
namespace Factory {


    IFactory * Factory::createResourceFactory(std::string & index)
    {

        IFactory * factory = nullptr;
        if ( index == "Interface::Resource::Factory::PollFactory" ) {
            factory = new PollFactory();
        }

        if ( index == "Interface::Resource::Factory::PollVoteFactory" ) {
            factory = new VoteFactory();
        }

        if ( index == "Interface::Resource::Factory::ApplicationFactory" ) {
            factory = new ApplicationFactory();
        }

        return factory;

    }


} } }
