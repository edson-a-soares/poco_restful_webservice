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

#ifndef Adapter_Database_SQLiteDataAccessManager_INCLUDED
#define Adapter_Database_SQLiteDataAccessManager_INCLUDED

#include "Poco/Data/SessionFactory.h"
#include "Foundation/Persistence/Database/DataAccessManagerInterface.h"

namespace Database {


    class SQLiteDataAccessManager : public ::Foundation::Persistence::Database::DataAccessManagerInterface
    {
    public:
        SQLiteDataAccessManager() = delete;
        ~SQLiteDataAccessManager() override;
        explicit SQLiteDataAccessManager(const std::string & database);
        Poco::Data::Session & session() override;
        std::unique_ptr<::Foundation::Persistence::Database::TableGatewayInterface> tableGateway() override;

    private:
        Poco::Data::Session _session;

    };


}

#endif
