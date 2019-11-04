#include "Poco/Data/MySQL/Connector.h"
#include "Adapter/Database/MySQLTableGateway.h"
#include "Adapter/Database/MySQLDataAccessManager.h"

namespace Database {


    MySQLDataAccessManager::MySQLDataAccessManager(const std::string & host,
                                                   const std::string & username,
                                                   const std::string & password,
                                                   const std::string & database)
        : CONNECTION_STRING(
              "host="     + host      + "; "
              "db="       + database  + "; "
              "user="     + username  + "; "
              "password=" + password
          ),
         _session(Poco::Data::MySQL::Connector::KEY, CONNECTION_STRING)
    {}

    MySQLDataAccessManager::~MySQLDataAccessManager()
    {
        Poco::Data::MySQL::Connector::unregisterConnector();
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
