#include "gtest/gtest.h"

#include "Poco/SQL/MySQL/Connector.h"
#include "Infrastructure/Persistence/TableGateway.h"

using namespace Poco::SQL::Keywords;

class TableGatewayTest : public ::testing::Test
{
protected:

    void SetUp() override
    {

        Poco::SQL::MySQL::Connector::registerConnector();
        auto session = connectionManager.getSession();

        // Drop test table, if it exists.
        session << "DROP TABLE IF EXISTS tablegatewaytest", now;

        // (re)create table
        session << "CREATE TABLE tablegatewaytest ("
                        "identity VARCHAR(36) NOT NULL, "
                        "nickname VARCHAR(15), "
                        "fullname VARCHAR(25) NOT NULL, "
                        "PRIMARY KEY (identity)"
                    ")", now;

        tableGateway = new Infrastructure::Persistence::TableGateway(session);

    }

    void TearDown() override
    {

        auto session = connectionManager.getSession();

        // Drop test table.
        session << "DROP TABLE tablegatewaytest", now;

        delete tableGateway;
        Poco::SQL::MySQL::Connector::registerConnector();

    }

    Infrastructure::Persistence::ConnectionManager connectionManager;
    Infrastructure::Persistence::ITableGateway * tableGateway = nullptr;

};

TEST_F(TableGatewayTest, testInsertFeature)
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

    Poco::SQL::RecordSet recordSet =
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

TEST_F(TableGatewayTest, testUpdateFeature)
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
        .updateWhere("identity", UUID);

    Poco::SQL::RecordSet recordSet =
        (*tableGateway)
            .table("tablegatewaytest")
            .selectWhere("identity", UUID);

    ASSERT_TRUE(recordSet.rowCount() == 1);
    ASSERT_EQ(  recordSet.value("identity", 0).toString(), UUID);
    ASSERT_EQ(  recordSet.value("nickname", 0).toString(), nickname);
    ASSERT_EQ(  recordSet.value("fullname", 0).toString(), fullname);

}

TEST_F(TableGatewayTest, testRemoveFeature)
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

    Poco::SQL::RecordSet recordSet =
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

TEST_F(TableGatewayTest, testInvalidArgumentExceptionForColumsListEmpty)
{

    ASSERT_THROW((*tableGateway).table("tablegatewaytest").insert(),
        Poco::InvalidArgumentException
    );

    ASSERT_THROW((*tableGateway).table("tablegatewaytest").updateWhere("", ""),
        Poco::InvalidArgumentException
    );

}
