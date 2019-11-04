#include "Adapter/Database/DataSource.h"
#include "Adapter/Database/MySQLDataAccessManager.h"
#include "Adapter/Database/SQLiteDataAccessManager.h"
#include "Foundation/Persistence/Database/DataAccessManagerFactory.h"
#include "Foundation/Persistence/Database/DataAccessManagerInterface.h"

#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/SQLite/Connector.h"

namespace Foundation {
namespace Persistence {
namespace Database {


    std::unique_ptr<DataAccessManagerInterface> DataAccessManagerFactory::create()
    {
        auto dataSource = ::Database::DataSource::create();
        std::unique_ptr<Foundation::Persistence::Database::DataAccessManagerInterface> dataAccessManager = nullptr;

        switch (dataSource->adapter()) {
            case Foundation::Persistence::Database::SQLite:
                Poco::Data::SQLite::Connector::registerConnector();
                dataAccessManager = std::make_unique<::Database::SQLiteDataAccessManager>(dataSource->database());
                break;

            case Foundation::Persistence::Database::MySQL:
                Poco::Data::MySQL::Connector::registerConnector();
                dataAccessManager =
                    std::make_unique<::Database::MySQLDataAccessManager>(
                            dataSource->hostname(),
                            dataSource->username(),
                            dataSource->password(),
                            dataSource->database()
                        );
                break;
        }

        return dataAccessManager;
    }


} } }
