#include "Poco/String.h"
#include "Poco/Exception.h"
#include "Adapter/Database/DataSource.h"
#include "Adapter/Database/DataSourceFileReader.h"
#include "Adapter/Database/DataSourceConfigurationFile.h"

namespace Database {


    DataSource::DataSource(std::unique_ptr<Foundation::IO::JsonFileReaderInterface> fileReader)
        : _fileReader(std::move(fileReader)),
          adapters {
              { "mysql",  Foundation::Persistence::Database::MySQL  },
              { "sqlite", Foundation::Persistence::Database::SQLite }
          }
    {}

    std::string DataSource::username()
    {
        return _fileReader->fetch("username");
    }

    std::string DataSource::password()
    {
        return _fileReader->fetch("password");
    }

    std::string DataSource::hostname()
    {
        return _fileReader->fetch("hostname");
    }

    std::string DataSource::database()
    {
        return _fileReader->fetch("database");
    }

    Foundation::Persistence::Database::DatabaseAdapter DataSource::adapter()
    {
        auto adapterString = Poco::toLower(_fileReader->fetch("adapter"));
        if ( adapters.find(adapterString) == adapters.end() )
            throw Poco::InvalidArgumentException(
                "Invalid Database Adapter",
                "There's no such database adapter " + adapterString
            );

        return adapters.at(adapterString);
    }

    std::unique_ptr<Foundation::Persistence::Database::DataSourceInterface> DataSource::create()
    {
        return std::make_unique<DataSource>(
            std::make_unique<DataSourceFileReader>(
                std::make_unique<DataSourceConfigurationFile>()
            )
        );
    }


}
