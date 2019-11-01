#include <string>
#include <memory>
#include <gtest/gtest.h>
#include "Adapter/Database/DataSource.h"
#include "Adapter/Database/DataSourceFileReader.h"
#include "Foundation/Persistence/Database/DatabaseAdapter.h"
#include "Foundation/Persistence/Database/DataSourceInterface.h"
#include "Adapter/Database/Context/FakeDataSourceConfigurationFile.h"

class DataSourceTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        dataSource = std::make_unique<Database::DataSource>(
            std::make_unique<Database::DataSourceFileReader>(
                std::make_unique<UnitTests::Database::Context::FakeDataSourceConfigurationFile>()
            )
        );
    }

    std::unique_ptr<Foundation::Persistence::Database::DataSourceInterface> dataSource  = nullptr;

};

TEST_F(DataSourceTest, DataSourceFromFile) {

    ASSERT_EQ("123456789",                              dataSource->password());
    ASSERT_EQ("127.0.0.1",                              dataSource->hostname());
    ASSERT_EQ("webservice_schema",                      dataSource->database());
    ASSERT_EQ(Foundation::Persistence::Database::SQLite,dataSource->adapter());

}
