#include "gtest/gtest.h"
#include "Poco/DateTime.h"
#include "Poco/Exception.h"
#include "Poll/Domain/Model/Option.h"

TEST(OptionTest, testOptionValidEntity)
{

    Poll::Domain::Model::Option newOption;

    newOption.positionAt(1);
    newOption.withText("This is the Option one.");

    ASSERT_TRUE( newOption.positionedAt() == 1 );
    ASSERT_TRUE( newOption.text() == "This is the Option one." );

    // Creation and Update date must keep the relationship where creation is a time before update.
    ASSERT_TRUE( newOption.createdAt() < newOption.lastUpdatedAt() );

}

TEST(OptionTest, testOptionInvalidPositionException)
{

    Poll::Domain::Model::Option newOption;

    ASSERT_THROW(
        newOption.positionAt(-5),
        Poco::InvalidArgumentException
    );

    ASSERT_THROW(
        newOption.positionAt(0),
        Poco::InvalidArgumentException
    );

}

TEST(OptionTest, testInvalidUpdateDate)
{

    ASSERT_THROW(
            Poll::Domain::Model::Option newOption(
            "8a9b7c9b-d026-48e9-99a4-6d002a625b82",
            Poco::DateTime(2018, 01, 01),
            Poco::DateTime(2017, 12, 30)
        ),
        Poco::InvalidArgumentException
    );

}
