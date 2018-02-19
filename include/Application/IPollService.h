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

#ifndef Web_Service_Application_IPoll_Service_INCLUDED
#define Web_Service_Application_IPoll_Service_INCLUDED

#include <list>
#include <string>
#include "Domain/Model/Poll/Vote.h"
#include "Domain/Model/Poll/Question.h"

namespace Application {


    /// A pair of question options and their amount of votes.
    typedef std::pair<std::string, int> PollResult;
    class IPollService
    {
    public:
        virtual ~IPollService() = default;

        /*!
         * It add a vote to one question option.
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
        virtual void changeQuestion(const Domain::Model::Poll::Question & question) = 0;

        /*!
         * @param question The question to be created.
         * @return The identity of the question created.
         */
        virtual std::string newQuestion(const Domain::Model::Poll::Question & question) = 0;

        /*!
         * @param identity The identity of the question.
         * @return The question, if it is found.
         */
        virtual Domain::Model::Poll::Question findQuestion(const std::string & identity) = 0;

    };


}

#endif
