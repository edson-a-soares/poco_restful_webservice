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

#ifndef Web_Service_Domain_Model_Poll_IQuestion_Repository_INCLUDED
#define Web_Service_Domain_Model_Poll_IQuestion_Repository_INCLUDED

#include <list>
#include <string>
#include "Domain/Model/Poll/Question.h"

namespace Domain {
namespace Model {
namespace Poll {


    class IQuestionRepository
    {
    public:
        virtual ~IQuestionRepository() = default;

        /*!
         * It saves a given Question.
         *
         * @param question The question to save.
         */
        virtual void store(const Domain::Model::Poll::Question &) = 0;

        /*!
         * It updates a given Question data.
         *
         * @param question The question to be updated.
         */
        virtual void update(const Domain::Model::Poll::Question &) = 0;

        /*!
         * It destroys completely a question and its related data.
         *
         * @param question The Question to be erased.
         */
        virtual void erase(const Domain::Model::Poll::Question &) = 0;

        /*!
         * It finds a Question using its identity.
         *
         * @param identity The Question's identity.
         * @return The Question, if found. If not, it throws an exception.
         */
        virtual Domain::Model::Poll::Question withIdentity(const std::string &) = 0;

    };


} } }

#endif
