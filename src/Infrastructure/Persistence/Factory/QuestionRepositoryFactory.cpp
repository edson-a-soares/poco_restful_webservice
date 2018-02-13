#include "Poco/Data/MySQL/Connector.h"
#include "Infrastructure/Persistence/Factory/QuestionRepositoryFactory.h"
#include "Infrastructure/Persistence/QuestionRepository.h"

namespace Infrastructure {
namespace Persistence {


    Domain::Model::Poll::IQuestionRepository * QuestionRepositoryFactory::create()
    {
        Infrastructure::Persistence::ConnectionManager connectionManager;

        Poco::Data::MySQL::Connector::registerConnector();
        auto session = connectionManager.getSession();
        return new Infrastructure::Persistence::QuestionRepository(session);
    }


} }
