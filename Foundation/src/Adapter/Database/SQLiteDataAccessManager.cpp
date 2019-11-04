#include "Poco/Data/SQLite/Connector.h"
#include "Adapter/Database/SQLiteTableGateway.h"
#include "Adapter/Database/SQLiteDataAccessManager.h"

namespace Database {


    SQLiteDataAccessManager::SQLiteDataAccessManager(const std::string & database)
        : _session("SQLite", database + ".db")
    {}

    SQLiteDataAccessManager::~SQLiteDataAccessManager()
    {
        Poco::Data::SQLite::Connector::unregisterConnector();
    }

    Poco::Data::Session & SQLiteDataAccessManager::session()
    {
        return _session;
    }

    std::unique_ptr<::Foundation::Persistence::Database::TableGatewayInterface> SQLiteDataAccessManager::tableGateway()
    {
        return std::make_unique<::Database::SQLiteTableGateway>(_session);
    }


}
