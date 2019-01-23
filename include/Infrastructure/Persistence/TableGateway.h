/*
 * (C) Copyright 2018 Edson (http://edsonaraujosoares.com) and others.
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

#ifndef Web_Service_Infrastructure_Persistence_Table_Gateway_INCLUDED
#define Web_Service_Infrastructure_Persistence_Table_Gateway_INCLUDED

#include <list>
#include "Poco/SQL/Session.h"
#include "Infrastructure/Persistence/ITableGateway.h"
#include "Infrastructure/Persistence/ConnectionManager.h"

namespace Infrastructure {
namespace Persistence {


    class TableGateway final : public ITableGateway
    {
    public:
        explicit TableGateway(Poco::SQL::Session &);

        void insert() override;
        ITableGateway & throwException(bool) override;
        ITableGateway & table(const std::string &) final;
        ITableGateway & withColumn(const std::string &) final;
        void removeWhere(const std::string &, const std::string &) final;
        void updateWhere(const std::string &, const std::string &) override;
        ITableGateway & withColumn(const std::string &, const std::string &) final;
        Poco::SQL::RecordSet selectWhere(const std::string &, const std::string &) final;

    protected:
        std::string queryColumns() const;

    private:
        std::string _table;
        bool _throwException;
        Poco::SQL::Session _session;
        std::list<std::string> _columns;
        std::map<std::string, std::string> _columnsValues;

    };


} }

#endif
