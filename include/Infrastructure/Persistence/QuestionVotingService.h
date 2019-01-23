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

#ifndef Web_Service_Infrastructure_Persistence_Question_Voting_Service_INCLUDED
#define Web_Service_Infrastructure_Persistence_Question_Voting_Service_INCLUDED

#include "Domain/Service/IQuestionVotingService.h"
#include "Infrastructure/Persistence/TableGateway.h"

namespace Infrastructure {
namespace Persistence {


    class QuestionVotingService : public Domain::Service::IQuestionVotingService
    {
    public:
        explicit QuestionVotingService(Poco::SQL::Session &);
        ~QuestionVotingService() override;

        std::list<Domain::Model::Poll::Vote> votesFor(const Domain::Model::Poll::Question &) override;
        void voteOn(const Domain::Model::Poll::Question &, const Domain::Model::Poll::Vote &) override;

    private:
        Poco::SQL::Session _session;


    };


} }

#endif
