#include "Infrastructure/Persistence/ConnectionManager.h"

#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"

namespace Infrastructure {
namespace Persistence {


    ConnectionManager::ConnectionManager()
        : db(),
          host(),
          user(),
          password()
    {
        init();
    }

    void ConnectionManager::init()
    {

        std::string environment;
        auto environmentVariableValue = std::getenv("POCO_API_ENVIRONMENT");
        if ( environmentVariableValue != nullptr )
            environment = std::string(environmentVariableValue);

        if ( environment.empty() || environment == "development" ) {
            user="developer";
            password="abc12345";
            host="127.0.0.1";
            db="poco_webservice_schema";
        }

        if ( environment == "build" ) {
            user="ci_environment";
            password="abc12345";
            host="127.0.0.1";
            db="poco_webservice_schema";
        }

    }

    Poco::Data::Session ConnectionManager::getSession()
    {
        std::string connectionString = "host=" + host + "; user=" + user + "; password=" + password +"; db=" + db;
        return Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, connectionString);
    }


} }
