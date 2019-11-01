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

    namespace Foundation = Foundation::Persistence::Database;
    class AbstractTableGateway : public Foundation::TableGatewayInterface
    {
    public:
        AbstractTableGateway() = delete;
        ~AbstractTableGateway() override = default;

        void insert() override;
        Foundation::TableGatewayInterface & throwException(bool) final;
        Foundation::TableGatewayInterface & table(const std::string &) final;
        Foundation::TableGatewayInterface & withColumn(const std::string &) final;
        void removeWhere(const std::string &, const std::string &) final;
        void updateWhere(const std::string &, const std::string &) override;
        Foundation::TableGatewayInterface & withColumn(const std::string &, const std::string &) final;
        Poco::Data::RecordSet selectWhere(const std::string &, const std::string &) final;

    protected:
        explicit AbstractTableGateway(Poco::Data::Session &);
        std::string queryColumns() const;

    private:
        std::string _table;
        bool _throwException;
        Poco::Data::Session _session;
        std::list<std::string> _columns;
        std::map<std::string, std::string> _columnsValues;

    };


}

#endif
