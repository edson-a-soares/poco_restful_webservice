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

#ifndef Database_QuestionRepository_INCLUDED
#define Database_QuestionRepository_INCLUDED

#include "Poll/Domain/Model/Option.h"
#include "Poll/Domain/Model/QuestionRepositoryInterface.h"
#include "Foundation/Persistence/Database/DataAccessManagerInterface.h"

namespace Database {


    class QuestionRepository final : public Poll::Domain::Model::QuestionRepositoryInterface
    {
    public:
        QuestionRepository() = delete;
        ~QuestionRepository() override = default;
        explicit QuestionRepository(std::unique_ptr<Foundation::Persistence::Database::DataAccessManagerInterface>);
        void add(const Poll::Domain::Model::Question &) override;
        void remove(const Poll::Domain::Model::Question &) override;
        Poll::Domain::Model::Question withIdentity(const std::string &) override;

    private:
        std::unique_ptr<Foundation::Persistence::Database::DataAccessManagerInterface> dataAccessManager;

        Poco::DateTime toDate(const std::string & dateTime);
        std::string toString(const Poco::DateTime & dateTime);

    };


}

#endif
