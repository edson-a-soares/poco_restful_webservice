#include "Infrastructure/Persistence/ConnectionManager.h"

#include "Poco/SQL/SessionFactory.h"
#include "Poco/SQL/MySQL/Connector.h"
#include "Poco/SQL/MySQL/MySQLException.h"

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
        auto environmentVariableValue = std::getenv("POCO_WEBSERVICE_ENVIRONMENT");
        if ( environmentVariableValue != nullptr )
            environment = std::string(environmentVariableValue);

        if ( environment.empty() || environment == "local" ) {
            user="developer";
            password="abc123456";
            host="127.0.0.1";
            db="poco_webservice_schema";
        }

        if ( environment == "development" ) {
            user="developer";
            password="abc123456";
            host="database";
            db="poco_webservice_schema";
        }

        if ( environment == "build" ) {
            user="ci_environment";
            password="abc12345";
            host="127.0.0.1";
            db="poco_webservice_schema";
        }

    }

    Poco::SQL::Session ConnectionManager::getSession()
    {
        std::string connectionString = "host=" + host + "; user=" + user + "; password=" + password +"; db=" + db;
        return Poco::SQL::SessionFactory::instance().create(Poco::SQL::MySQL::Connector::KEY, connectionString);
    }


} }
