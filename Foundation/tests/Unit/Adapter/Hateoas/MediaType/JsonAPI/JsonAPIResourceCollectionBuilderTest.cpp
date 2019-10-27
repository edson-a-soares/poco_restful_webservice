#include <vector>
#include <string>
#include "gtest/gtest.h"
#include "Foundation/Hateoas/MediaTypeFactory.h"
#include "Adapter/Hateoas/MediaType/JsonAPI/Context/FakeBookObject.h"

class JsonAPIResourceCollectionBuilderTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        UnitTests::Hateoas::Context::FakeBookObject theOldManAndTheSea  { "1", "The Old Man and the Sea" };
        UnitTests::Hateoas::Context::FakeBookObject forWhomTheBellTolls { "2", "For Whom the Bell Tolls" };
        UnitTests::Hateoas::Context::FakeBookObject endersGame          { "3", "Enders Game" };

        booksList.emplace_back(theOldManAndTheSea);
        booksList.emplace_back(forWhomTheBellTolls);
        booksList.emplace_back(endersGame);
    }

    std::vector<UnitTests::Hateoas::Context::FakeBookObject> booksList;

};

TEST_F(JsonAPIResourceCollectionBuilderTest, GetBasicResourceCollectionAsJsonString)
{

    auto expectedJson =
    "{ "
        "\"data\" : [ "
            "{ "
                "\"attributes\" : { "
                    "\"title\" : \"The Old Man and the Sea\" "
                "}, "
                "\"id\" : \"1\", "
                "\"type\" : \"book\" "
            "}, "
            "{ "
                "\"attributes\" : { "
                    "\"title\" : \"For Whom the Bell Tolls\" "
                "}, "
                "\"id\" : \"2\", "
                "\"type\" : \"book\" "
            "}, "
            "{ "
                "\"attributes\" : { "
                    "\"title\" : \"Enders Game\" "
                "}, "
                "\"id\" : \"3\", "
                "\"type\" : \"book\" "
            "} "
        "] "
    "}";

    auto collection =  Foundation::Hateoas::MediaTypeFactory::create()->collection();
    for ( auto const & book : booksList ) {

        auto resource = Foundation::Hateoas::MediaTypeFactory::create()->resource();

        resource->withType("book");
        resource->withIdentity(book.identity);
        resource->addAttribute("title", book.title);

        collection->addResource(std::move(resource));

    }

    ASSERT_EQ(expectedJson, collection->toString());

}

TEST_F(JsonAPIResourceCollectionBuilderTest, GetResourceCollectionWithMetadataAsJsonString)
{

    auto expectedJson =
    "{ "
        "\"data\" : [ "
            "{ "
                "\"attributes\" : { "
                    "\"title\" : \"The Old Man and the Sea\" "
                "}, "
                "\"id\" : \"1\", "
                "\"type\" : \"book\" "
            "}, "
            "{ "
                "\"attributes\" : { "
                    "\"title\" : \"For Whom the Bell Tolls\" "
                "}, "
                "\"id\" : \"2\", "
                "\"type\" : \"book\" "
            "}, "
            "{ "
                "\"attributes\" : { "
                    "\"title\" : \"Enders Game\" "
                "}, "
                "\"id\" : \"3\", "
                "\"type\" : \"book\" "
            "} "
        "], "
        "\"meta\" : { "
            "\"copyright\" : \"Copyright 2019 Poco RESTful API\", "
            "\"jsonapi\" : \"1.1\", "
            "\"langs\" : [ \"en-US\", \"pt-BR\" ] "
        "} "
    "}";

    auto collection =  Foundation::Hateoas::MediaTypeFactory::create()->collection();

    Poco::Dynamic::Array langs;
    langs.emplace_back("en-US");
    langs.emplace_back("pt-BR");

    collection->withMetadata("langs", langs);
    collection->withMetadata("jsonapi", "1.1");
    collection->withMetadata("copyright", "Copyright 2019 Poco RESTful API");

    for ( auto const & book : booksList ) {

        auto resource = Foundation::Hateoas::MediaTypeFactory::create()->resource();

        resource->withType("book");
        resource->withIdentity(book.identity);
        resource->addAttribute("title", book.title);

        collection->addResource(std::move(resource));

    }

    ASSERT_EQ(expectedJson, collection->toString());

}
