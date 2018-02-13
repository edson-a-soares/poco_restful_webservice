#include <string>
#include "gtest/gtest.h"
#include "Domain/Model/Poll/Question.h"
#include "Interface/Handling/JsonAPIResourceBuilder.h"

class QuestionResourceTest : public ::testing::Test
{
protected:

    void SetUp() override
    {

        question = new Domain::Model::Poll::Question(
            "ef2e0c14-f7fe-11e7-9aac-0023aeea22d3",
            {},
            Poco::DateTime(2018, 01, 10, 23, 50, 00),
            Poco::DateTime(2018, 01, 11, 13, 30, 00)
        );

        question->withLabel("You know what ...");
        question->withDetails("Details really matter!");
        question->withText("Does it is the place to question?");

        resourceBuilder = new Interface::Handling::JsonAPIResourceBuilder("test.example.com");

        json =
        "{ "
            "\"data\" : [ "
                "{ "
                    "\"attributes\" : { "
                        "\"created_at\" : \"2018-01-10T23:50:00Z\", "
                        "\"details\" : \"Details really matter!\", "
                        "\"ends_at\" : \"0000-01-01T00:00:00Z\", "
                        "\"label\" : \"You know what ...\", "
                        "\"last_updated_at\" : \"2018-01-11T13:30:00Z\", "
                        "\"text\" : \"Does it is the place to question?\" "
                    "}, "
                    "\"id\" : \"ef2e0c14-f7fe-11e7-9aac-0023aeea22d3\", "
                    "\"links\" : { "
                        "\"first\" : \"http:\\/\\/test.example.com\\/poll\\/2ae7f21a-af90-4ef8-8691-8ad85bbebe6a\", "
                        "\"last\" : \"http:\\/\\/test.example.com\\/poll\\/6bf18c95-4bd0-45ef-a112-7911763d87b4\", "
                        "\"next\" : \"http:\\/\\/test.example.com\\/poll\\/33cf91db-4800-4525-9ed5-7067e147bf13\", "
                        "\"prev\" : \"http:\\/\\/test.example.com\\/poll\\/cd4a3277-3d51-4a36-b0c9-75cdb95971d0\", "
                        "\"self\" : \"http:\\/\\/test.example.com\\/poll\\/ef2e0c14-f7fe-11e7-9aac-0023aeea22d3\" "
                    "}, "
                    "\"type\" : \"questions\" "
                "} "
            "], "
            "\"meta\" : { "
                "\"copyright\" : \"Copyright 2018 Poco RESTful API\", "
                "\"jsonapi\" : \"1.1\", "
                "\"langs\" : [ "
                    "\"en-US\", "
                    "\"pt-BR\" "
                "] "
            "} "
        "}";

    }

    void TearDown() override
    {
        delete question;
        delete resourceBuilder;
    }

    std::string json;
    Domain::Model::Poll::Question * question = nullptr;
    Interface::Handling::JsonAPIResourceBuilder * resourceBuilder = nullptr;

};

TEST_F(QuestionResourceTest, testQuestionResourceBuilderToJson)
{

    resourceBuilder->withType("questions");
    resourceBuilder->withIdentity(question->identity());

    resourceBuilder->addAttribute("text", question->text());
    resourceBuilder->addAttribute("label", question->label());
    resourceBuilder->addAttribute("details", question->details());
    resourceBuilder->addAttribute("ends_at", question->endAt());
    resourceBuilder->addAttribute("created_at", question->createdAt());
    resourceBuilder->addAttribute("last_updated_at", question->lastUpdatedAt());

    resourceBuilder->linkTo("self", "/poll/" + question->identity());
    resourceBuilder->linkTo("next", "/poll/33cf91db-4800-4525-9ed5-7067e147bf13");
    resourceBuilder->linkTo("prev", "/poll/cd4a3277-3d51-4a36-b0c9-75cdb95971d0");
    resourceBuilder->linkTo("last", "/poll/6bf18c95-4bd0-45ef-a112-7911763d87b4");
    resourceBuilder->linkTo("first", "/poll/2ae7f21a-af90-4ef8-8691-8ad85bbebe6a");

    // Defining Metadata Options
    Poco::Dynamic::Array langs;
    langs.emplace_back("en-US");
    langs.emplace_back("pt-BR");

    resourceBuilder->withMetadata("langs", langs);
    resourceBuilder->withMetadata("jsonapi", "1.1");
    resourceBuilder->withMetadata("copyright", "Copyright 2018 Poco RESTful API");

    ASSERT_EQ(json, resourceBuilder->build().toString());

}
