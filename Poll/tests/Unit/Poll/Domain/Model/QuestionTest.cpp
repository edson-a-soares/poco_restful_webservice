#include <list>
#include "gtest/gtest.h"
#include "Poco/DateTime.h"
#include "Poco/Exception.h"
#include "Poll/Domain/Model/Option.h"
#include "Poll/Domain/Model/Question.h"

class QuestionTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        Poll::Domain::Model::Option firstCreated;
        firstCreated.withText("This is the first Option.");
        firstCreated.positionAt(1);
        newQuestion.add(firstCreated);

        Poll::Domain::Model::Option secondCreated;
        secondCreated.withText("This is the second Option.");
        secondCreated.positionAt(2);
        newQuestion.add(secondCreated);

        Poll::Domain::Model::Option thirdCreated;
        thirdCreated.withText("This is the third Option.");
        thirdCreated.positionAt(3);
        newQuestion.add(thirdCreated);

        Poll::Domain::Model::Option fourthCreated;
        fourthCreated.withText("This is the fourth Option.");
        fourthCreated.positionAt(4);
        newQuestion.add(fourthCreated);
    }

    Poll::Domain::Model::Question newQuestion;

};

TEST_F(QuestionTest, QuestionRelationalOperators)
{

    Poll::Domain::Model::Question anotherQuestion;

    ASSERT_TRUE( anotherQuestion == anotherQuestion);
    ASSERT_FALSE(newQuestion == anotherQuestion);
    ASSERT_TRUE( newQuestion == newQuestion);

    ASSERT_TRUE( anotherQuestion != newQuestion);
    ASSERT_FALSE(anotherQuestion != anotherQuestion);

}

TEST_F(QuestionTest, QuestionEndingDateTime)
{

    Poll::Domain::Model::Question someQuestion;

    someQuestion.startAt(Poco::DateTime(2015, 01, 01));
    someQuestion.endAt(  Poco::DateTime(2015, 02, 01));

    ASSERT_FALSE(someQuestion.opened());

    Poll::Domain::Model::Question anotherQuestion(
        "6ad58558-1b91-4d1f-ad8c-bf995313d554",
        Poco::DateTime(2015, 11, 10),
        Poco::DateTime(2015, 12, 01),
        {},
        Poco::DateTime(2016, 01, 05),
        Poco::DateTime(2050, 01, 05)
    );

    ASSERT_TRUE(anotherQuestion.opened());

}

TEST_F(QuestionTest, InvalidUpdateDate)
{

    ASSERT_THROW(
            Poll::Domain::Model::Question someQuestion(
            "8a9b7c9b-d026-48e9-99a4-6d002a625b82",
            Poco::DateTime(2018, 01, 01),
            Poco::DateTime(2017, 12, 30),
            {}
        ),
        Poco::IllegalStateException
    );

}

TEST_F(QuestionTest, InvalidEndDate)
{

    ASSERT_THROW(
            Poll::Domain::Model::Question someQuestion(
            "8a9b7c9b-d026-48e9-99a4-6d002a625b82",
            Poco::DateTime(2018, 01, 01),
            Poco::DateTime(2018, 02, 25),
            {},
            Poco::DateTime(2018, 02, 25),
            Poco::DateTime(2017, 01, 30)
        ),
        Poco::IllegalStateException
    );

}
