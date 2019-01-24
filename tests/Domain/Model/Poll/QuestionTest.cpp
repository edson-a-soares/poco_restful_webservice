#include "gtest/gtest.h"

#include <list>
#include "Poco/DateTime.h"
#include "Poco/Exception.h"
#include "Domain/Model/Poll/Option.h"
#include "Domain/Model/Poll/Question.h"

class QuestionTest : public ::testing::Test
{
protected:

    void SetUp() override
    {

        Domain::Model::Poll::Option firstCreated;
        firstCreated.withText("This is the first Option.");
        firstCreated.positionAt(1);
        newQuestion.add(firstCreated);

        Domain::Model::Poll::Option secondCreated;
        secondCreated.withText("This is the second Option.");
        secondCreated.positionAt(2);
        newQuestion.add(secondCreated);

        Domain::Model::Poll::Option thirdCreated;
        thirdCreated.withText("This is the third Option.");
        thirdCreated.positionAt(3);
        newQuestion.add(thirdCreated);

        Domain::Model::Poll::Option fourthCreated;
        fourthCreated.withText("This is the fourth Option.");
        fourthCreated.positionAt(4);
        newQuestion.add(fourthCreated);

    }

    Domain::Model::Poll::Question newQuestion;

};

TEST_F(QuestionTest, testQuestionBasicOperators)
{

    Domain::Model::Poll::Question secondQuestion;

    // It tests different objects.
    ASSERT_TRUE(newQuestion != secondQuestion);
    ASSERT_FALSE(newQuestion == secondQuestion);

    // It tests the same object.
    ASSERT_FALSE(secondQuestion != secondQuestion);
    ASSERT_TRUE(secondQuestion == secondQuestion);

}

TEST_F(QuestionTest, testQuestionEndingDateTime)
{

    Domain::Model::Poll::Question someQuestion;

    someQuestion.startAt(Poco::DateTime(2015, 01, 01));
    someQuestion.endAt(Poco::DateTime(2015, 02, 01));

    ASSERT_FALSE(someQuestion.isOpened());

    Domain::Model::Poll::Question anotherQuestion(
        "6ad58558-1b91-4d1f-ad8c-bf995313d554",
        {},
        Poco::DateTime(2015, 11, 10),
        Poco::DateTime(2015, 12, 01),
        Poco::DateTime(2016, 01, 05),
        Poco::DateTime(2050, 01, 05)
    );

    ASSERT_TRUE(anotherQuestion.isOpened());

}

TEST_F(QuestionTest, testInvalidUpdateDate)
{

    ASSERT_THROW(
        Domain::Model::Poll::Question someQuestion(
            "8a9b7c9b-d026-48e9-99a4-6d002a625b82",
            {},
            Poco::DateTime(2018, 01, 01),
            Poco::DateTime(2017, 12, 30)
        ),
        Poco::IllegalStateException
    );

}

TEST_F(QuestionTest, testInvalidEndDate)
{

    ASSERT_THROW(
        Domain::Model::Poll::Question someQuestion(
            "8a9b7c9b-d026-48e9-99a4-6d002a625b82",
            {},
            Poco::DateTime(2018, 01, 01),
            Poco::DateTime(2018, 02, 25),
            Poco::DateTime(2018, 02, 25),
            Poco::DateTime(2017, 01, 30)
        ),
        Poco::IllegalStateException
    );

}
