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

#ifndef Web_Service_Infrastructure_Persistence_Option_Table_Gateway_INCLUDED
#define Web_Service_Infrastructure_Persistence_Option_Table_Gateway_INCLUDED

#include "Domain/Model/Poll/Option.h"
#include "Poco/SQL/SessionFactory.h"

namespace Infrastructure {
namespace Persistence {


    class OptionTableGateway
    {
    public:
        explicit OptionTableGateway(Poco::SQL::Session &);

        void update(const Domain::Model::Poll::Option &);
        void remove(const Domain::Model::Poll::Option &);
        void store(const std::string &, const Domain::Model::Poll::Option &);
        std::list<Domain::Model::Poll::Option> findOptions(const std::string &);
        void handleUpdate(const std::string &, const std::list<Domain::Model::Poll::Option> &);

    private:
        Poco::SQL::Session _session;

        /*!
         *
         * @param dateTime
         * @return
         */
        Poco::DateTime toDate(const std::string & dateTime);

        /*!
         *
         * @param dateTime
         * @return
         */
        std::string toString(const Poco::DateTime & dateTime);

    };


} }

#endif
