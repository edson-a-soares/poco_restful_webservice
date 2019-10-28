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

#ifndef Poll_Application_PollServiceInterface_INCLUDED
#define Poll_Application_PollServiceInterface_INCLUDED

#include <list>
#include <string>
#include "Poll/Domain/Model/Vote.h"
#include "Poll/Domain/Model/Question.h"

namespace Poll {
namespace Application {


    /// A pair of question options and their amount of votes.
    typedef std::pair<std::string, int> PollResult;
    class PollServiceInterface
    {
    public:
        virtual ~PollServiceInterface() = default;

        /*!
         * It adds a vote to one question option.
         *
         * @param questionIdentity The question identity.
         * @param optionIdentity The question's
         */
        virtual void voteOn(const std::string & questionIdentity, const std::string & optionIdentity) = 0;

        /*!
         * It gives the amount of votes to each option from a question.
         *
         * @param questionIdentity The question identity.
         * @return The list of options with the amount of values for each one.
         */
        virtual std::list<PollResult> requestResult(const std::string & questionIdentity) = 0;

        /*!
         * @param identity The question identity.
         */
        virtual void eraseQuestion(const std::string & identity) = 0;

        /*!
         * @param question The question to be updated.
         */
        virtual void changeQuestion(const Domain::Model::Question &) = 0;

        /*!
         * @param question The question to be created.
         * @return The identity of the question created.
         */
        virtual std::string newQuestion(const Domain::Model::Question &) = 0;

        /*!
         * @param identity The identity of the question.
         * @return The question, if it is found.
         */
        virtual Domain::Model::Question findQuestion(const std::string & identity) = 0;

    };


} }

#endif
