#include <string>
#include "gtest/gtest.h"
#include "Foundation/Hateoas/MediaTypeFactory.h"

class JsonAPIErrorBuilderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        expectedJson =
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

    std::string expectedJson;

};

TEST_F(JsonAPIErrorBuilderTest, GetErrorAsJsonString)
{

    auto error = Foundation::Hateoas::MediaTypeFactory::create()->error();

    error->withStatusCode(404);
    error->withType("Not Found");
    error->withDetails("This route does not exist.");
    error->sourceAt("http://example.com", "/something-to-pointer");

    ASSERT_EQ(expectedJson, error->toString());

}
