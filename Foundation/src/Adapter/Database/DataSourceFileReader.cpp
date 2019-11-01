#include "Adapter/Database/DataSourceFileReader.h"

namespace Database {


    DataSourceFileReader::DataSourceFileReader(std::unique_ptr<Foundation::Application::ConfigurationFileInterface> configurationFile)
        : AbstractJsonFileReader(
            std::move(configurationFile)->path(),
            {
                "adapter",
                "username",
                "password",
                "hostname",
                "database"
            }
        )
    {}


}
