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

#ifndef Web_Service_Infrastructure_Persistence_Database_Wrapper_INCLUDED
#define Web_Service_Infrastructure_Persistence_Database_Wrapper_INCLUDED

#include <string>
#include "Poco/SQL/Session.h"

namespace Infrastructure {
namespace Persistence {


    class ConnectionManager
    {
    public:
        ConnectionManager();

        Poco::SQL::Session getSession();

    private:
        std::string db;
        std::string host;
        std::string user;
        std::string password;

        void init();

    };


} }

#endif
