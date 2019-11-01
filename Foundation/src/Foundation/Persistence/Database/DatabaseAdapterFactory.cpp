#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Adapter/Database/MySQLTableGateway.h"
#include "Adapter/Database/SQLiteTableGateway.h"
#include "Foundation/Persistence/Database/DatabaseAdapterFactory.h"

namespace Foundation {
namespace Persistence {
namespace Database {


    std::unique_ptr<TableGatewayInterface> DatabaseAdapterFactory::create()
    {
        auto connectionParameters = ::Database::DataSourceFactory::create();

        if ( connectionParameters->adapter() == Foundation::Persistence::Database::SQLite ) {
            std::string database = connectionParameters->database() + ".db";
            Poco::Data::SQLite::Connector::registerConnector();
            auto session = Poco::Data::SessionFactory::instance().create("SQLite", database);
            return std::make_unique<::Database::SQLiteTableGateway>(session);
        }

        if ( connectionParameters->adapter() == Foundation::Persistence::Database::MySQL ) {
            std::string connectionString =
                "host="     + connectionParameters->hostname() + ";"
                "user="     + connectionParameters->username() + ";"
                "password=" + connectionParameters->password() + ";"
                "db="       + connectionParameters->database();

            Poco::Data::MySQL::Connector::registerConnector();
            auto session = Poco::Data::SessionFactory::instance().create("MySQL", connectionString);
            return std::make_unique<::Database::MySQLTableGateway>(session);
        }
    }


} } }
