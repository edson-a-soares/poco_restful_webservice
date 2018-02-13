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

#ifndef Web_Service_Application_Poll_Service_INCLUDED
#define Web_Service_Application_Poll_Service_INCLUDED

#include "Application/IPollService.h"
#include "Domain/Model/Poll/IQuestionRepository.h"
#include "Domain/Service/IQuestionVotingService.h"

namespace Application {


    class PollService final : public IPollService
    {
    public:

        /*!
         * @param repository A class that implements the Question repository interface.
         * @param service A class that implements the Question service interface.
         */
        PollService(
            Domain::Model::Poll::IQuestionRepository * repository,
            Domain::Service::IQuestionVotingService * service
        );

        ~PollService();

        /*!
         * @see IPollService::voteOn(const std::string &, const std::string &)
         */
        void voteOn(const std::string &, const std::string &) override;

        /*!
         * @see IPollService::requestResult(const std::string &)
         */
        std::list<PollResult> requestResult(const std::string & questionIdentity) override;

        /*!
         * @see IPollService::eraseQuestion(const std::string &)
         */
        void eraseQuestion(const std::string & identity) override;

        /*!
         * @see IPollService::changeQuestion(const Domain::Model::Poll::Question &)
         */
        void changeQuestion(const Domain::Model::Poll::Question &) override;

        /*!
         * @see IPollService::findQuestion(const std::string &)
         */
        Domain::Model::Poll::Question findQuestion(const std::string & identity) override;

        /*!
         * @see IPollService::newQuestion(const Domain::Model::Poll::Question &)
         */
        std::string newQuestion(const Domain::Model::Poll::Question & question) override;

    private:
        Domain::Service::IQuestionVotingService * votingService;
        Domain::Model::Poll::IQuestionRepository * questionRepository;

    };


}

#endif
