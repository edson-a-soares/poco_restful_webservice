/*
 * (C) Copyright 2019 Edson (http://edsonaraujosoares.com) and others.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contributors:
 *     Edson Araújo Soares
 */

#ifndef Foundation_Persistence_Database_TableGatewayInterface_INCLUDED
#define Foundation_Persistence_Database_TableGatewayInterface_INCLUDED

#include <string>
#include "Poco/Data/RecordSet.h"

namespace Foundation {
namespace Persistence {
namespace Database {


    /*!
     * It performs basic SQL operations in a database table.
     */
    class TableGatewayInterface
    {
    public:
        virtual ~TableGatewayInterface() = default;

        /*!
         * It inserts a new record into a database.
         */
        virtual void insert() = 0;

        /*!
         * It allows an exception throw in case of any anomalies like:
         *  - INSERT, UPDATE or DELETE with no rows inserted.
         *
         * @param flag It allows or not the exception thrown
         * @return A reference to itself for allowing to chain this method.
         */
        virtual TableGatewayInterface & throwException(bool flag) = 0;

        /*!
         * It defines the table where the operations should be performed.
         *
         * @param name The table name.
         * @return A reference to itself for allowing to chain this method.
         */
        virtual TableGatewayInterface & table(const std::string & name) = 0;

        /*!
         * It allows to specify the values of a column ina complex SQL query.
         *
         *  (*tableGateway)
         *     .table("table_name")
         *     .withColumn("first_column_name")
         *     .withColumn("second_column_name")
         *     .withColumn("third_column_name");
         *
         *     for(...) {
         *       (*tableGateway)
         *          .withValue("first_column_value")
         *          .withValue("second_column_value")
         *          .withValue("third_column_value")
         *      }
         *     tableGateway->insertAll();
         *
         * @param data The column value.
         * @return A reference to itself for allowing to chain this method.
         */
        virtual TableGatewayInterface & withValue(const std::string & data) = 0;

        /*!
         * It allows to specify which columns should be returned in a SQL query.
         *
         * tableGateway
         *     .table("table_name")
         *     .withColumn("first_column_name")
         *     .withColumn("second_column_name")
         *     .withColumn("third_column_name")
         *     .selectWhere("field_name", "field_value");
         *
         * @param column The columns name.
         * @return A reference to itself for allowing to chain this method.
         */
        virtual TableGatewayInterface & withColumn(const std::string & column) = 0;

        /*!
         * It deletes a specific row from a table database.
         *
         * @param column A reference column where to find the specific row to remove.
         * @param value  The value of the column chosen in order to find the row to be remove.
         */
        virtual void removeWhere(const std::string & column, const std::string & value) = 0;

        /*!
         * It deletes a specific row from a table database.
         *
         * @param column A reference column where to find the specific row to remove.
         * @param value  The value of the column chosen in order to find the row to be remove.
         */
        virtual void removeWhere(const std::string & column, const std::list<std::string> & values) = 0;

        /*!
         * It allows columns manipulation in SQL commands that need to.
         *
         * tableGateway
         *     .table("table_name")
         *     .withColumn("first_column_name",  "value")
         *     .withColumn("second_column_name", "value")
         *     .withColumn("third_column_name",  "value")
         *     .insert();
         *
         * @param column The column where to perform the operation.
         * @param value  The value to the chosen column.
         * @return A reference to itself for allowing to chain this method.
         */
        virtual TableGatewayInterface & withColumn(const std::string & column, const std::string & value) = 0;

        /*!
         * It performs a SQL select returns the results in a ResultSet.
         *
         * tableGateway
         *     .table("table_name")
         *     .withColumn("first_column_name",  "value")
         *     .withColumn("second_column_name", "value")
         *     .withColumn("third_column_name",  "value")
         *     .selectWhere("field_name", "field_value");
         *
         * @param column A reference column where to perform the query for a value.
         * @param value  The value of the column chosen in order to find the results expected.
         * @return The Results of the query.
         */
        virtual Poco::Data::RecordSet selectWhere(const std::string & column, const std::string & value) = 0;

    };


} } }

#endif
