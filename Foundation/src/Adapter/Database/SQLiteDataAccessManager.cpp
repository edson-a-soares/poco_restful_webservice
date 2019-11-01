#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Adapter/Database/SQLiteTableGateway.h"
#include "Adapter/Database/SQLiteDataAccessManager.h"

namespace Database {


    SQLiteDataAccessManager::SQLiteDataAccessManager(const std::string & database)
        : _session("")
    {
        Poco::Data::SQLite::Connector::registerConnector();
        _session = Poco::Data::SessionFactory::instance().create("SQLite", database + ".db");
    }

    Poco::Data::Session& SQLiteDataAccessManager::session()
    {
        return _session;
    }

    std::unique_ptr<::Foundation::Persistence::Database::TableGatewayInterface> SQLiteDataAccessManager::tableGateway()
    {
        return std::make_unique<::Database::SQLiteTableGateway>(_session);
    }


}
