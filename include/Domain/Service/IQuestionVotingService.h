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

#ifndef Web_Service_Domain_Service_IQuestion_Voting_Service_INCLUDED
#define Web_Service_Domain_Service_IQuestion_Voting_Service_INCLUDED

#include "Domain/Model/Poll/Vote.h"
#include "Domain/Model/Poll/Question.h"

namespace Domain {
namespace Service {


    class IQuestionVotingService
    {
    public:
        virtual ~IQuestionVotingService() = default;

        /*!
         * It performs a vote on a Question.
         *
         * @param question  The Question on which one wishes vote for.
         * @param vote      The vote; Option chosen and its related data.
         */
        virtual void voteOn(const Model::Poll::Question & question, const Model::Poll::Vote & vote) = 0;

        /*!
         * It retrieves all votes given to a Question.
         *
         * @param question A Question to get its results.
         * @return A list with all votes given to a question.
         */
        virtual std::list<Domain::Model::Poll::Vote> votesFor(const Model::Poll::Question & question) = 0;

    };


} }

#endif
