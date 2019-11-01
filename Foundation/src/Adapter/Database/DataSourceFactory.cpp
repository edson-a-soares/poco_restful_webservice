#include "Adapter/Database/DataSource.h"
#include "Adapter/Database/DataSourceFactory.h"
#include "Adapter/Database/DataSourceFileReader.h"
#include "Adapter/Database/DataSourceConfigurationFile.h"

namespace Database {


    std::unique_ptr<::Foundation::Persistence::Database::DataSourceInterface> DataSourceFactory::create()
    {
        return std::make_unique<DataSource>(
                std::make_unique<DataSourceFileReader>(
                    std::make_unique<DataSourceConfigurationFile>()
                )
            );
    }


}
