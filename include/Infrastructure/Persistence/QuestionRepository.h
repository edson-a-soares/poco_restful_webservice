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

#ifndef Web_Service_Infrastructure_Persistence_Question_Repository_INCLUDED
#define Web_Service_Infrastructure_Persistence_Question_Repository_INCLUDED

#include "Domain/Model/Poll/IQuestionRepository.h"
#include "Infrastructure/Persistence/ConnectionManager.h"

namespace Infrastructure {
namespace Persistence {


    class QuestionRepository final : public Domain::Model::Poll::IQuestionRepository
    {
    public:
        explicit QuestionRepository(Poco::SQL::Session &);
        ~QuestionRepository() override;

        void store(const Domain::Model::Poll::Question &) override;
        void erase(const Domain::Model::Poll::Question &) override;
        void update(const Domain::Model::Poll::Question &) override;
        Domain::Model::Poll::Question withIdentity(const std::string &) override;

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
