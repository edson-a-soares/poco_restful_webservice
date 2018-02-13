#include <string>
#include "gtest/gtest.h"
#include "Interface/Handling/JSONAPI/JsonAPIErrorBuilder.h"

class JsonAPIErrorBuilderTest : public ::testing::Test
{
protected:

    void SetUp() override
    {

        errorBuilder = new Interface::Handling::JsonAPIErrorBuilder("http://example.com");

        errorBuilder->withStatusCode(404);
        errorBuilder->withType("Not Found");
        errorBuilder->sourceAt("/something-to-pointer");
        errorBuilder->withDetails("This route does not exist.");

        json =
        "{ "
            "\"error\" : [ "
                        "{ "
                    "\"details\" : \"This route does not exist.\", "
                    "\"source\" : { "
                        "\"pointer\" : \"http:\\/\\/example.com\\/something-to-pointer\" "
                    "}, "
                    "\"status\" : 404, "
                    "\"type\" : \"Not Found\" "
                "} "
            "] "
        "}";

    }

    void TearDown() override
    {
        delete errorBuilder;
    }

    std::string json;
    Interface::Handling::IJsonAPIErrorBuilder * errorBuilder = nullptr;

};

TEST_F(JsonAPIErrorBuilderTest, testErrorJsonRepresentationBuilding)
{

    Poco::DynamicStruct jsonAPIError = errorBuilder->build();
    ASSERT_EQ(json, jsonAPIError.toString());

}
