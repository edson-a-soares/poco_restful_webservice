#include <string>
#include <memory>
#include "gtest/gtest.h"
#include "Foundation/Hateoas/MediaTypeFactory.h"

class JsonAPIResourceBuilderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        expectedJson =
        "{ "
            "\"data\" : [ "
                "{ "
                    "\"attributes\" : { "
                        "\"body\" : \"The shortest article. Ever.\", "
                        "\"created_at\" : \"2015-05-22T14:56:29.000Z\", "
                        "\"last_updated_at\" : \"2015-05-22T14:56:28.000Z\", "
                        "\"title\" : \"JSON:API paints my bikeshed!\" "
                    "}, "
                    "\"id\" : \"3\", "
                    "\"links\" : { "
                        "\"first\" : \"http:\\/\\/api.example.com\\/article\\/1\", "
                        "\"last\" : \"http:\\/\\/api.example.com\\/article\\/5\", "
                        "\"next\" : \"http:\\/\\/api.example.com\\/article\\/4\", "
                        "\"prev\" : \"http:\\/\\/api.example.com\\/article\\/2\", "
                        "\"self\" : \"http:\\/\\/api.example.com\\/article\\/3\" "
                    "}, "
                    "\"type\" : \"articles\" "
                "} "
            "], "
            "\"meta\" : { "
                "\"copyright\" : \"Copyright 2019 Poco RESTful API\", "
                "\"jsonapi\" : \"1.1\", "
                "\"langs\" : [ "
                    "\"en-US\", "
                    "\"pt-BR\" "
                "] "
            "} "
        "}";
    }

    std::string expectedJson;

};

TEST_F(JsonAPIResourceBuilderTest, GetResourceAsJsonString)
{

    auto resource =  Foundation::Hateoas::MediaTypeFactory::create()->resource();

    resource->withIdentity("3");
    resource->withType("articles");
    resource->hostedAt("api.example.com");

    resource->addAttribute("title", "JSON:API paints my bikeshed!");
    resource->addAttribute("body", "The shortest article. Ever.");
    resource->addAttribute("created_at", "2015-05-22T14:56:29.000Z");
    resource->addAttribute("last_updated_at", "2015-05-22T14:56:28.000Z");

    resource->linkTo("self",  "/article/3");
    resource->linkTo("next",  "/article/4");
    resource->linkTo("prev",  "/article/2");
    resource->linkTo("last",  "/article/5");
    resource->linkTo("first", "/article/1");

    Poco::Dynamic::Array langs;
    langs.emplace_back("en-US");
    langs.emplace_back("pt-BR");

    resource->withMetadata("langs", langs);
    resource->withMetadata("jsonapi", "1.1");
    resource->withMetadata("copyright", "Copyright 2019 Poco RESTful API");

    ASSERT_EQ(expectedJson, resource->toString());

}
