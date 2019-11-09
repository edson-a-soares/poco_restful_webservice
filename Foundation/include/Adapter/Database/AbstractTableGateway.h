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

#ifndef Database_AbstractTableGateway_INCLUDED
#define Database_AbstractTableGateway_INCLUDED

#include <list>
#include "Poco/Data/Session.h"
#include "Foundation/Persistence/Database/TableGatewayInterface.h"

namespace Database {

    ///
    namespace Persistence = Foundation::Persistence::Database;

    class AbstractTableGateway : public Persistence::TableGatewayInterface
    {
    public:
        AbstractTableGateway() = delete;
        ~AbstractTableGateway() override = default;

        void insert() override;
        Persistence::TableGatewayInterface & throwException(bool) final;
        Persistence::TableGatewayInterface & table(const std::string & name) final;

        Poco::Data::RecordSet selectWhere(const std::string & column, const std::string & value) override;

        Persistence::TableGatewayInterface & withValue(const std::string &) final;
        Persistence::TableGatewayInterface & withColumn(const std::string & name) final;
        Persistence::TableGatewayInterface & withColumn(const std::string & name, const std::string & value) final;

        void removeWhere(const std::string & column, const std::string & value) override;
        void removeWhere(const std::string & column, const std::list<std::string> & values) override;

    protected:
        explicit AbstractTableGateway(Poco::Data::Session &);

        bool throwException();
        void clearColumnsData();
        std::string tableName();
        std::list<std::string> columnNames();
        std::list<std::string> columnValues();

        std::string selectQueryColumns() const;
        std::string separateItByCommas(const std::list<std::string> &) const;
        static std::list<std::string> singleQuoteIt(const std::list<std::string> &);
        virtual std::string columnConflictClauseFormat(const std::list<std::string> & columns) const;
        std::string insertInstructionValues(const std::list<std::string> & columnNames, const std::list<std::string> & columnValues);

    private:
        bool _throwException;
        std::string _tableName;
        Poco::Data::Session _session;
        std::list<std::string> _columnNames;
        std::list<std::string> _columnValues;

    };


}

#endif
