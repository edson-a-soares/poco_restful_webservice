#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Adapter/Database/MySQLTableGateway.h"
#include "Adapter/Database/MySQLDataAccessManager.h"

namespace Database {


    MySQLDataAccessManager::MySQLDataAccessManager(const std::string & host,
                                                   const std::string & username,
                                                   const std::string & password,
                                                   const std::string & database)
        : _session(""),
          connectionString()
    {
        connectionString =
            "host="     + host     + ";"
            "user="     + username + ";"
            "password=" + password + ";"
            "db="       + database;

        Poco::Data::MySQL::Connector::registerConnector();
        _session = Poco::Data::SessionFactory::instance().create("MySQL", connectionString);
    }

    Poco::Data::Session & MySQLDataAccessManager::session()
    {
        return _session;
    }

    std::unique_ptr<::Foundation::Persistence::Database::TableGatewayInterface> MySQLDataAccessManager::tableGateway()
    {
        return std::make_unique<::Database::MySQLTableGateway>(_session);
    }


}
