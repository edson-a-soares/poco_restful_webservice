#include <string>
#include <memory>
#include <gtest/gtest.h>
#include "Adapter/Http/CORSConfiguration.h"
#include "Adapter/Http/CORSConfigurationFileReader.h"
#include "Adapter/Http/Context/FakeCORSConfigurationFile.h"

class CORSConfigurationTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        corsHandler = std::make_unique<Http::CORSConfiguration>(
            std::make_unique<Http::CORSConfigurationFileReader>(
                std::make_unique<UnitTests::File::Context::FakeCORSConfigurationFile>()
            )
        );
    }

    std::unique_ptr<Foundation::Http::CORSConfigurationInterface> corsHandler  = nullptr;

};

TEST_F(CORSConfigurationTest, CORSDataFromFile) {

    auto headers = corsHandler->headers();

    ASSERT_EQ("microsoft.com, localhost:8080, 127.0.0.2:3206", headers["Access-Control-Allow-Origin"]);
    ASSERT_EQ("GET, POST, PUT, DELETE, PATH, OPTIONS",         headers["Access-Control-Request-Method"]);
    ASSERT_EQ("Accept, Content-Type, Accept-Language",         headers["Access-Control-Request-Headers"]);
    ASSERT_EQ("true",                                          headers["Access-Control-Allow-Credentials"]);

}
