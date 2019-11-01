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

#ifndef Database_DataSource_INCLUDED
#define Database_DataSource_INCLUDED

#include <map>
#include <string>
#include <memory>
#include "Foundation/IO/JsonFileReaderInterface.h"
#include "Foundation/Persistence/Database/DataSourceInterface.h"

namespace Database {


    class DataSource : public Foundation::Persistence::Database::DataSourceInterface
    {
    public:
        explicit DataSource(std::unique_ptr<Foundation::IO::JsonFileReaderInterface>);
        std::string username() final;
        std::string password() final;
        std::string hostname() final;
        std::string database() final;
        Foundation::Persistence::Database::DatabaseAdapter adapter() final;
        static std::unique_ptr<Foundation::Persistence::Database::DataSourceInterface> create();

    private:
        std::unique_ptr<Foundation::IO::JsonFileReaderInterface> _fileReader;
        std::map<std::string, Foundation::Persistence::Database::DatabaseAdapter> adapters;

    };


}

#endif
