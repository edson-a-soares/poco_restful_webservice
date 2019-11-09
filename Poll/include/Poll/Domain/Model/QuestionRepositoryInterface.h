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

#ifndef Poll_Domain_Model_QuestionRepositoryInterface_INCLUDED
#define Poll_Domain_Model_QuestionRepositoryInterface_INCLUDED

#include <list>
#include <string>
#include "Poll/Domain/Model/Question.h"

namespace Poll {
namespace Domain {
namespace Model {


    class QuestionRepositoryInterface
    {
    public:
        virtual ~QuestionRepositoryInterface() = default;

        /*!
         * It either stores or updates a given question.
         *
         * @param question The question to handled.
         */
        virtual void add(const Question &) = 0;

        /*!
         * It deletes a question and all its related data.
         *
         * @param question The Question to be erased.
         */
        virtual void remove(const Question &) = 0;

        /*!
         * It finds a question using its unique identity.
         *
         * As David
         *
         * @param identity The question's identity.
         * @return The question, if found. If not, it throws an exception.
         */
        virtual Question withIdentity(const std::string &) = 0;

    };


} } }

#endif
