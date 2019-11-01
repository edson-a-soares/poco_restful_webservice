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

#ifndef Foundation_Persistence_Database_DataAccessManagerInterface_INCLUDED
#define Foundation_Persistence_Database_DataAccessManagerInterface_INCLUDED

#include <memory>
#include "Poco/Data/Session.h"
#include "Foundation/Persistence/Database/TableGatewayInterface.h"

namespace Foundation {
namespace Persistence {
namespace Database {


    class DataAccessManagerInterface
    {
    public:
        virtual ~DataAccessManagerInterface() = default;
        virtual Poco::Data::Session & session() = 0;
        virtual std::unique_ptr<Foundation::Persistence::Database::TableGatewayInterface> tableGateway() = 0;

    };


} } }

#endif
