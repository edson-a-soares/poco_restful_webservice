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

#ifndef Foundation_Persistence_Database_DataAccessManagerFactory_INCLUDED
#define Foundation_Persistence_Database_DataAccessManagerFactory_INCLUDED

#include <memory>
#include "Foundation/Persistence/Database/DataSourceInterface.h"
#include "Foundation/Persistence/Database/TableGatewayInterface.h"
#include "Foundation/Persistence/Database/DataAccessManagerInterface.h"

namespace Foundation {
namespace Persistence {
namespace Database {


    class DataAccessManagerFactory
    {
    public:
        DataAccessManagerFactory()  = delete;
        ~DataAccessManagerFactory() = delete;
        static std::unique_ptr<DataAccessManagerInterface> create();

    };


} } }

#endif
