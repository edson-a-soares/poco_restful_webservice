#include <string>
#include "gtest/gtest.h"
#include "Poco/UUIDGenerator.h"
#include "Foundation/Domain/Model/Context/FakeDomainModelObject.h"

class EntityObjectTest : public ::testing::Test
{};

TEST_F(EntityObjectTest, ValidObjectOverloadedOperatorsUsage)
{

    UnitTests::Foundation::Context::FakeDomainModelObject domainObjectOne, domainObjectTwo;

    ASSERT_TRUE (domainObjectOne != domainObjectTwo);
    ASSERT_FALSE(domainObjectOne == domainObjectTwo);

}

TEST_F(EntityObjectTest, ObjectConstructionWithValidIdentity)
{

    auto identity = Poco::UUIDGenerator().createRandom().toString();
    ASSERT_NO_THROW(UnitTests::Foundation::Context::FakeDomainModelObject domainObject(identity));

}

TEST_F(EntityObjectTest, InvalidArgumentExceptionOnObjectConstruction)
{

    ASSERT_THROW(
        UnitTests::Foundation::Context::FakeDomainModelObject domainObject("123456789"),
        Poco::InvalidArgumentException
    );

}
