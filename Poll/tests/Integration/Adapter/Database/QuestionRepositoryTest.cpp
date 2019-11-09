#include <memory>
#include "gtest/gtest.h"
#include "Poll/Domain/Model/Question.h"
#include "Foundation/Domain/Model/Identity.h"
#include "Adapter/Database/QuestionRepository.h"
#include "Poll/Domain/QuestionNotFoundException.h"
#include "Foundation/Persistence/Database/DataAccessManagerFactory.h"

class QuestionRepositoryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        questionRepository = std::make_unique<Database::QuestionRepository>(
                Foundation::Persistence::Database::DataAccessManagerFactory::create()
            );
    }

    std::unique_ptr<Poll::Domain::Model::QuestionRepositoryInterface> questionRepository = nullptr;

};

TEST_F(QuestionRepositoryTest, QuestionAddition)
{

    Poll::Domain::Model::Question newQuestion;

    newQuestion.withLabel("Be ready for a new question.");
    newQuestion.withText("Should not this be a new question?");
    newQuestion.withDetails("This has everything to be a new question, but let us make sure it really is.");

    questionRepository->add(newQuestion);
    auto retrievedQuestion = questionRepository->withIdentity(newQuestion.identity());
    ASSERT_TRUE(retrievedQuestion.identity() == newQuestion.identity());

    ASSERT_TRUE(newQuestion.createdAt().day() == retrievedQuestion.createdAt().day()
        && newQuestion.createdAt().month()  == retrievedQuestion.createdAt().month()
        && newQuestion.createdAt().year()   == retrievedQuestion.createdAt().year()
        && newQuestion.createdAt().hour()   == retrievedQuestion.createdAt().hour()
        && newQuestion.createdAt().minute() == retrievedQuestion.createdAt().minute()
    );

    ASSERT_TRUE(newQuestion.lastUpdatedAt().day() == retrievedQuestion.lastUpdatedAt().day()
        && newQuestion.lastUpdatedAt().month()  == retrievedQuestion.lastUpdatedAt().month()
        && newQuestion.lastUpdatedAt().year()   == retrievedQuestion.lastUpdatedAt().year()
        && newQuestion.lastUpdatedAt().hour()   == retrievedQuestion.lastUpdatedAt().hour()
        && newQuestion.lastUpdatedAt().minute() == retrievedQuestion.lastUpdatedAt().minute()
    );

    questionRepository->remove(newQuestion);

}

TEST_F(QuestionRepositoryTest, QuestionEdition)
{

    Poll::Domain::Model::Question newQuestion;

    newQuestion.withLabel("Label of an updating question.");
    newQuestion.withDetails("Details of an updating question.");
    newQuestion.withText("Does it this the question to be updated?");

    questionRepository->add(newQuestion);
    auto retrievedQuestion = questionRepository->withIdentity(newQuestion.identity());

    retrievedQuestion.withLabel("Label of an updated question.");
    retrievedQuestion.withDetails("Details of an updated question.");
    retrievedQuestion.withText("Does it this the last updated question?");

    questionRepository->add(retrievedQuestion);
    auto updatedQuestion = questionRepository->withIdentity(retrievedQuestion.identity());

    ASSERT_EQ(updatedQuestion.label(),   "Label of an updated question.");
    ASSERT_EQ(updatedQuestion.details(), "Details of an updated question.");
    ASSERT_EQ(updatedQuestion.text(),    "Does it this the last updated question?");

    questionRepository->remove(updatedQuestion);

}
