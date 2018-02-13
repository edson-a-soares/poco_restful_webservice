#include "Poco/Exception.h"
#include "Application/PollService.h"
#include "Interface/Resource/Exception.h"
#include "Domain/Model/Poll/QuestionNotFoundException.h"

#include <algorithm>

namespace Application {


    PollService::PollService(
        Domain::Model::Poll::IQuestionRepository * _repository,
        Domain::Service::IQuestionVotingService * service
    )
        : votingService(service),
          questionRepository(_repository)
    { }

    PollService::~PollService()
    {
        delete votingService;
        delete questionRepository;
    }


    void PollService::voteOn(const std::string & questionId, const std::string & optionId)
    {

        try {

            auto question = questionRepository->withIdentity(questionId);

            Domain::Model::Poll::Vote vote(optionId);
            votingService->voteOn(question, vote);

        } catch(Poco::Exception & exception) {
            throw Interface::Resource::Exception("Bad Request", exception.message(), 400);
        }

    }

    std::list<PollResult> PollService::requestResult(const std::string & questionIdentity)
    {

        Domain::Model::Poll::Question question(questionIdentity);

        auto votesCollection    = votingService->votesFor(question);
        auto optionsCollection  = questionRepository->withIdentity(questionIdentity).options();

        std::list<PollResult> pollResults;
        for ( auto const & option : optionsCollection )
            pollResults.emplace_back(std::make_pair(option.identity(), 0));

        for ( auto const & vote : votesCollection ) {

            auto iterator = std::find_if(pollResults.begin(), pollResults.end(),
                [vote](const PollResult & result) {
                    return vote.optionIdentity() == result.first;
                }
            );

            /// Increment the amount of vote to the option,
            /// if the item is in the list already.
            if ( iterator != pollResults.end() )
                iterator->second++;

        }

        return pollResults;

    }

    void PollService::eraseQuestion(const std::string & identity)
    {

        try {

            Domain::Model::Poll::Question question(identity);
            questionRepository->erase(question);

        } catch (Domain::Model::Poll::QuestionNotFoundException & exception) {
            throw Interface::Resource::Exception("Not Found", exception.message(), 404);
        } catch (Poco::Exception & exception) {
            throw Interface::Resource::Exception("Bad Request", exception.message(), 400);
        }

    }

    void PollService::changeQuestion(const Domain::Model::Poll::Question & question)
    {

        try {
            questionRepository->store(question);
        } catch (Poco::Exception & exception) {
            throw Interface::Resource::Exception("Bad Request", exception.message(), 400);
        }

    }

    Domain::Model::Poll::Question PollService::findQuestion(const std::string & identity)
    {

        try {
            return questionRepository->withIdentity(identity);
        } catch (Domain::Model::Poll::QuestionNotFoundException & exception) {
            throw Interface::Resource::Exception("Not Found", exception.message(), exception.code());
        } catch (Poco::Exception & exception) {
            throw Interface::Resource::Exception("Bad Request", exception.message(), exception.code());
        }

    }

    std::string PollService::newQuestion(const Domain::Model::Poll::Question & question)
    {

        try {
            questionRepository->store(question);
        } catch (Poco::Exception & exception) {
            throw Interface::Resource::Exception("Bad Request", exception.message(), 400);
        }

        return question.identity();

    }


}
