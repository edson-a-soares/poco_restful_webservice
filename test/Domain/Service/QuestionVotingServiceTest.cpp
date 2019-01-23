#include "gtest/gtest.h"

#include "Poco/SQL/MySQL/Connector.h"
#include "Domain/Model/Poll/Vote.h"
#include "Domain/Model/Poll/QuestionNotFoundException.h"
#include "Infrastructure/Persistence/ConnectionManager.h"
#include "Infrastructure/Persistence/QuestionRepository.h"
#include "Infrastructure/Persistence/QuestionVotingService.h"

class QuestionVotingServiceTest : public ::testing::Test
{
protected:

    void SetUp() override
    {

        Infrastructure::Persistence::ConnectionManager connectionManager;

        Poco::SQL::MySQL::Connector::registerConnector();

        auto session = connectionManager.getSession();
        allQuestions  = new Infrastructure::Persistence::QuestionRepository(session);
        votingService = new Infrastructure::Persistence::QuestionVotingService(session);

    }

    void TearDown() override
    {
        delete allQuestions;
        delete votingService;
    }

    Domain::Model::Poll::IQuestionRepository * allQuestions = nullptr;
    Domain::Service::IQuestionVotingService * votingService = nullptr;

};

TEST_F(QuestionVotingServiceTest, testVoteOnAndVotesForQuestion)
{

    Domain::Model::Poll::Question newQuestion;
    newQuestion.withText("Does it is this the question to be voted?");

    Domain::Model::Poll::Option firstOption;
    firstOption.withText("First option to be voted.");
    firstOption.positionAt(1);
    newQuestion.add(firstOption);

    Domain::Model::Poll::Option secondOption;
    secondOption.withText("Second option to be voted.");
    secondOption.positionAt(2);
    newQuestion.add(secondOption);

    allQuestions->store(newQuestion);
    auto retrievedQuestion = allQuestions->withIdentity(newQuestion.identity());

    ASSERT_TRUE(retrievedQuestion.identity() == newQuestion.identity());
    ASSERT_TRUE(retrievedQuestion.options().size() == 2);

    for ( int counter = 0; counter < 50; counter++ ) {
        Domain::Model::Poll::Vote vote(firstOption.identity());
        votingService->voteOn(retrievedQuestion, vote);
    }

    auto votesCollection = votingService->votesFor(retrievedQuestion);
    ASSERT_TRUE( votesCollection.size() == 50 );

    allQuestions->erase(retrievedQuestion);

}
