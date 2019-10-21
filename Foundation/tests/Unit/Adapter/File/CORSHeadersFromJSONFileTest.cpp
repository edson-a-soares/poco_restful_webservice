#include <string>
#include <memory>
#include <gtest/gtest.h>
#include "Adapter/File/CORSHeadersFromJSONFile.h"
#include "Adapter/File/CORSHeadersJSONFileReader.h"
#include "Adapter/File/Context/StubCORSHeadersFile.h"

class CORSHeadersFromJSONFileTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        corsHandler = std::make_unique<File::CORSHeadersFromJSONFile>(
            std::make_unique<File::CORSHeadersJSONFileReader>(
                std::make_unique<UnitTests::File::Context::StubCORSHeadersFile>()
            )
        );
    }

    std::unique_ptr<Foundation::Http::CORSHeadersInterface> corsHandler  = nullptr;

};

TEST_F(CORSHeadersFromJSONFileTest, CORSHeaders) {

    auto headers = corsHandler->headers();

    ASSERT_EQ("microsoft.com, localhost:8080, 127.0.0.2:3206", headers["Access-Control-Allow-Origin"]);
    ASSERT_EQ("GET, POST, PUT, DELETE, PATH, OPTIONS",         headers["Access-Control-Request-Method"]);
    ASSERT_EQ("Accept, Content-Type, Accept-Language",         headers["Access-Control-Request-Headers"]);
    ASSERT_EQ("true",                                          headers["Access-Control-Allow-Credentials"]);

}
