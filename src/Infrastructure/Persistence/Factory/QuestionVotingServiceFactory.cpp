#include "Poco/Data/MySQL/Connector.h"
#include "Infrastructure/Persistence/QuestionVotingService.h"
#include "Infrastructure/Persistence/Factory/QuestionVotingServiceFactory.h"

namespace Infrastructure {
namespace Persistence {


    Domain::Service::IQuestionVotingService * QuestionVotingServiceFactory::create()
    {
        Infrastructure::Persistence::ConnectionManager connectionManager;

        Poco::Data::MySQL::Connector::registerConnector();
        auto session = connectionManager.getSession();

        return new QuestionVotingService(session);
    }


} }
