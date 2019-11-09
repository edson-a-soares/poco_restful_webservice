#include "gtest/gtest.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Adapter/Database/SQLiteTableGateway.h"
#include "Foundation/Persistence/Database/TableGatewayInterface.h"

using namespace Poco::Data::Keywords;

class SQLiteTableGatewayTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        Poco::Data::SQLite::Connector::registerConnector();
        Poco::Data::Session session("SQLite", DATABASE_PATH);

        session << "DROP TABLE IF EXISTS tablegatewaytest", now;

        // (re)create table
        session << "CREATE TABLE tablegatewaytest ("
                        "identity VARCHAR(36) NOT NULL, "
                        "nickname VARCHAR(15), "
                        "fullname VARCHAR(25) NOT NULL, "
                        "PRIMARY KEY (identity)"
                    ")", now;

        tableGateway = std::make_unique<Database::SQLiteTableGateway>(session);
    }

    void TearDown() override
    {
        Poco::Data::Session session("SQLite", DATABASE_PATH);
        session << "DROP TABLE tablegatewaytest", now;
    }

    const std::string DATABASE_PATH = std::string(TESTS_DATA_PATH) + "/testing_sqlite_database.db";
    std::unique_ptr<Foundation::Persistence::Database::TableGatewayInterface> tableGateway = nullptr;

};

TEST_F(SQLiteTableGatewayTest, InsertOperation)
{

    const std::string nickname = "Waltz";
    const std::string fullname = "Walter Hartwell White";
    const std::string UUID = "ddb4b35b-fdf8-4ba2-a57a-cc4658d710bb";

    (*tableGateway)
        .throwException(true)
        .table("tablegatewaytest")
        .withColumn("identity", UUID)
        .withColumn("nickname", nickname)
        .withColumn("fullname", fullname)
        .insert();

    Poco::Data::RecordSet recordSet =
        (*tableGateway)
            .table("tablegatewaytest")
            .withColumn("identity")
            .withColumn("fullname")
            .withColumn("nickname")
            .selectWhere("identity", UUID);

    ASSERT_TRUE(recordSet.rowCount() == 1);
    ASSERT_EQ(  recordSet.value("identity", 0).toString(), UUID);
    ASSERT_EQ(  recordSet.value("nickname", 0).toString(), nickname);
    ASSERT_EQ(  recordSet.value("fullname", 0).toString(), fullname);

}

TEST_F(SQLiteTableGatewayTest, UpdateOperarion)
{

    const std::string nickname  = "Heisenberg";
    const std::string fullname  = "Walter Hartwell White";
    const std::string UUID      = "dbb845ac-35d1-4454-9390-e0a8926e5635";

    (*tableGateway)
        .throwException(true)
        .table("tablegatewaytest")
        .withColumn("identity", UUID)
        .withColumn("nickname", "Waltz")
        .withColumn("fullname", fullname)
        .insert();

    (*tableGateway)
        .throwException(true)
        .table("tablegatewaytest")
        .withColumn("fullname", fullname)
        .withColumn("nickname", nickname)
        .withColumn("identity", UUID)
        .insert();

    Poco::Data::RecordSet recordSet =
        (*tableGateway)
            .table("tablegatewaytest")
            .selectWhere("identity", UUID);

    ASSERT_TRUE(recordSet.rowCount() == 1);
    ASSERT_EQ(  recordSet.value("identity", 0).toString(), UUID);
    ASSERT_EQ(  recordSet.value("nickname", 0).toString(), nickname);
    ASSERT_EQ(  recordSet.value("fullname", 0).toString(), fullname);

}

TEST_F(SQLiteTableGatewayTest, RemoveOperation)
{

    const std::string nickname  = "Heisenberg";
    const std::string fullname  = "Walter Hartwell White";
    const std::string UUID      = "082a2f64-1659-4099-8cb0-c6c724102dba";

    (*tableGateway)
        .throwException(true)
        .table("tablegatewaytest")
        .withColumn("identity", UUID)
        .withColumn("nickname", nickname)
        .withColumn("fullname", fullname)
        .insert();

    Poco::Data::RecordSet recordSet =
        (*tableGateway)
            .table("tablegatewaytest")
            .selectWhere("identity", UUID);

    ASSERT_TRUE(recordSet.rowCount() == 1);
    ASSERT_EQ(  recordSet.value("identity", 0).toString(), UUID);
    ASSERT_EQ(  recordSet.value("nickname", 0).toString(), nickname);
    ASSERT_EQ(  recordSet.value("fullname", 0).toString(), fullname);

    (*tableGateway)
        .throwException(true)
        .table("tablegatewaytest")
        .removeWhere("identity", UUID);

    auto foundRows =
        (*tableGateway)
            .table("tablegatewaytest")
            .selectWhere("identity", UUID)
            .rowCount();

    ASSERT_TRUE(foundRows == 0);

}

TEST_F(SQLiteTableGatewayTest, AssertionViolationExceptionForEmptyColumsList)
{

    ASSERT_THROW(
        (*tableGateway).table("tablegatewaytest").insert(),
        Poco::AssertionViolationException
    );

}
