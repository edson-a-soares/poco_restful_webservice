#include "gtest/gtest.h"

#include "Poco/SQL/MySQL/Connector.h"
#include "Domain/Model/Poll/Question.h"
#include "Infrastructure/Persistence/ConnectionManager.h"
#include "Domain/Model/Poll/QuestionNotFoundException.h"
#include "Infrastructure/Persistence/QuestionRepository.h"

class QuestionRepositoryTest : public ::testing::Test
{
protected:

    void SetUp() override
    {

        Infrastructure::Persistence::ConnectionManager connectionManager;

        Poco::SQL::MySQL::Connector::registerConnector();
        auto session = connectionManager.getSession();

        allQuestions = new Infrastructure::Persistence::QuestionRepository(session);

    }

    void TearDown() override
    {
        delete allQuestions;
    }

    Domain::Model::Poll::IQuestionRepository * allQuestions = nullptr;

};

TEST_F(QuestionRepositoryTest, testStoreAndEraseQuestion)
{

    Domain::Model::Poll::Question newQuestion;

    newQuestion.withLabel("Be ready for a new question.");
    newQuestion.withText("Should not this be a new question?");
    newQuestion.withDetails("This has everything to be a new question, but let us make sure it really is.");

    allQuestions->store(newQuestion);
    auto returnedQuestion = allQuestions->withIdentity(newQuestion.identity());

    ASSERT_TRUE(newQuestion.identity() == returnedQuestion.identity());

    ASSERT_TRUE(
        newQuestion.createdAt().day()    == returnedQuestion.createdAt().day()    &&
        newQuestion.createdAt().month()  == returnedQuestion.createdAt().month()  &&
        newQuestion.createdAt().year()   == returnedQuestion.createdAt().year()   &&
        newQuestion.createdAt().hour()   == returnedQuestion.createdAt().hour()   &&
        newQuestion.createdAt().minute() == returnedQuestion.createdAt().minute()
    );

    ASSERT_TRUE(
        newQuestion.lastUpdatedAt().day()    == returnedQuestion.lastUpdatedAt().day()    &&
        newQuestion.lastUpdatedAt().month()  == returnedQuestion.lastUpdatedAt().month()  &&
        newQuestion.lastUpdatedAt().year()   == returnedQuestion.lastUpdatedAt().year()   &&
        newQuestion.lastUpdatedAt().hour()   == returnedQuestion.lastUpdatedAt().hour()   &&
        newQuestion.lastUpdatedAt().minute() == returnedQuestion.lastUpdatedAt().minute()
    );

    allQuestions->erase(newQuestion);
    ASSERT_THROW(allQuestions->erase(newQuestion),
        Domain::Model::Poll::QuestionNotFoundException
    );

}

TEST_F(QuestionRepositoryTest, testQuestionUpdate)
{

    /// It creates a question to be tested.
    Domain::Model::Poll::Question newQuestion;

    newQuestion.withLabel("Label of an updating question.");
    newQuestion.withDetails("Details of an updating question.");
    newQuestion.withText("Does it this the question to be updated?");

    allQuestions->store(newQuestion);

    /// It retrieves and changes the question options to, only then, updating them.
    auto retrievedQuestion = allQuestions->withIdentity(newQuestion.identity());

    retrievedQuestion.withLabel("Label of an updated question.");
    retrievedQuestion.withDetails("Details of an updated question.");
    retrievedQuestion.withText("Does it this the last updated question?");

    allQuestions->update(retrievedQuestion);

    /// It retrieves the updated option to check its fields.
    auto updatedQuestion = allQuestions->withIdentity(retrievedQuestion.identity());

    ASSERT_EQ(updatedQuestion.label(),   "Label of an updated question.");
    ASSERT_EQ(updatedQuestion.details(), "Details of an updated question.");
    ASSERT_EQ(updatedQuestion.text(),    "Does it this the last updated question?");

    /// It deletes the question putting the database in the same state it was before the test.
    allQuestions->erase(updatedQuestion);
    ASSERT_THROW(allQuestions->erase(updatedQuestion),
        Domain::Model::Poll::QuestionNotFoundException
    );

}

TEST_F(QuestionRepositoryTest, testOptionsCollectionCreateOptions)
{

    ///
    Domain::Model::Poll::Question newQuestion;
    newQuestion.withText("Does it this the question to be updated?");

    Domain::Model::Poll::Option firstOptionCreated;
    firstOptionCreated.withText("First option to the update.");
    firstOptionCreated.positionAt(1);
    newQuestion.add(firstOptionCreated);

    Domain::Model::Poll::Option secondOptionCreated;
    secondOptionCreated.withText("Second option to the update.");
    secondOptionCreated.positionAt(2);
    newQuestion.add(secondOptionCreated);

    allQuestions->store(newQuestion);

    ///
    auto retrievedQuestion = allQuestions->withIdentity(newQuestion.identity());

    ASSERT_TRUE(retrievedQuestion.options().size() == 2);

    Domain::Model::Poll::Option thirdOptionCreated;
    thirdOptionCreated.withText("Third option to the update");
    thirdOptionCreated.positionAt(3);
    retrievedQuestion.add(thirdOptionCreated);

    Domain::Model::Poll::Option fourthOptionCreated;
    fourthOptionCreated.withText("Fourth option to the update");
    fourthOptionCreated.positionAt(4);
    retrievedQuestion.add(fourthOptionCreated);

    Domain::Model::Poll::Option fifthOptionCreated;
    fifthOptionCreated.withText("Fifth option to the update");
    fifthOptionCreated.positionAt(5);
    retrievedQuestion.add(fifthOptionCreated);

    allQuestions->update(retrievedQuestion);

    ///
    auto updatedQuestion = allQuestions->withIdentity(retrievedQuestion.identity());

    ASSERT_TRUE(updatedQuestion.options().size() == 5);

    /// Put the database in the same state it was before the test.
    allQuestions->erase(updatedQuestion);
    ASSERT_THROW(allQuestions->erase(updatedQuestion),
       Domain::Model::Poll::QuestionNotFoundException
    );

}

TEST_F(QuestionRepositoryTest, testOptionsCollectionUpdateOptions)
{

    ///
    Domain::Model::Poll::Question newQuestion;
    newQuestion.withText("Does it this the question to be updated?");

    Domain::Model::Poll::Option firstOptionCreated;
    firstOptionCreated.withText("First option to the update.");
    firstOptionCreated.positionAt(1);
    newQuestion.add(firstOptionCreated);

    Domain::Model::Poll::Option secondOptionCreated;
    secondOptionCreated.withText("Second option to the update.");
    secondOptionCreated.positionAt(2);
    newQuestion.add(secondOptionCreated);

    Domain::Model::Poll::Option thirdOptionCreated;
    thirdOptionCreated.withText("Third option to the update");
    thirdOptionCreated.positionAt(3);
    newQuestion.add(thirdOptionCreated);

    allQuestions->store(newQuestion);
    auto retrievedQuestion = allQuestions->withIdentity(newQuestion.identity());

    ASSERT_TRUE(retrievedQuestion.options().size() == 3);

    std::list<Domain::Model::Poll::Option>::iterator optionsIterator;

    auto retrievedOptions   = retrievedQuestion.options();
    optionsIterator         = retrievedOptions.begin();

    std::next(optionsIterator, 0)->withText("Question one already updated.");
    std::next(optionsIterator, 0)->positionAt(3);

    std::next(optionsIterator, 1)->withText("Question two already updated.");
    std::next(optionsIterator, 1)->positionAt(2);

    std::next(optionsIterator, 2)->withText("Question three already updated.");
    std::next(optionsIterator, 2)->positionAt(1);

    retrievedQuestion.setOptions(retrievedOptions);
    allQuestions->update(retrievedQuestion);

    /// It retrieves the updated option to check its fields.
    auto updatedQuestion = allQuestions->withIdentity(retrievedQuestion.identity());

    auto updatedOptions = updatedQuestion.options();
    optionsIterator     = updatedOptions.begin();

    ASSERT_EQ(std::next(optionsIterator, 0)->positionedAt(), 3);
    ASSERT_EQ(std::next(optionsIterator, 0)->text(), "Question one already updated.");

    ASSERT_EQ(std::next(optionsIterator, 1)->positionedAt(), 2);
    ASSERT_EQ(std::next(optionsIterator, 1)->text(), "Question two already updated.");

    ASSERT_EQ(std::next(optionsIterator, 2)->positionedAt(), 1);
    ASSERT_EQ(std::next(optionsIterator, 2)->text(), "Question three already updated.");

    /// Put the database in the same state it was before the test.
    allQuestions->erase(updatedQuestion);
    ASSERT_THROW(allQuestions->erase(updatedQuestion),
        Domain::Model::Poll::QuestionNotFoundException
    );

}

TEST_F(QuestionRepositoryTest, testOptionsCollectionDeleteOptions)
{

    /// It creates a question to be tested.
    Domain::Model::Poll::Question newQuestion;
    newQuestion.withText("Does it this the question to be updated?");

    Domain::Model::Poll::Option firstOptionCreated;
    firstOptionCreated.withText("First option to the update.");
    firstOptionCreated.positionAt(1);
    newQuestion.add(firstOptionCreated);

    Domain::Model::Poll::Option secondOptionCreated;
    secondOptionCreated.withText("Second option to the update.");
    secondOptionCreated.positionAt(2);
    newQuestion.add(secondOptionCreated);

    Domain::Model::Poll::Option thirdOptionCreated;
    thirdOptionCreated.withText("Third option to the update.");
    thirdOptionCreated.positionAt(3);
    newQuestion.add(thirdOptionCreated);

    allQuestions->store(newQuestion);

    /// It retrieves and changes the question options to, only then, updating them.
    auto retrievedQuestion = allQuestions->withIdentity(newQuestion.identity());

    ASSERT_TRUE(retrievedQuestion.options().size() == 3);

    auto options = retrievedQuestion.options();
    auto removingOption =
        std::remove_if(options.begin(), options.end(),
            [secondOptionCreated](const Domain::Model::Poll::Option & current) {
                return current.identity() == secondOptionCreated.identity();
            });

    options.erase(removingOption, options.end());

    options.back().positionAt(2);
    options.front().positionAt(1);
    retrievedQuestion.setOptions(options);

    allQuestions->update(retrievedQuestion);

    /// It retrieves the updated option to check its fields.
    auto updatedQuestion = allQuestions->withIdentity(newQuestion.identity());

    ASSERT_TRUE(updatedQuestion.options().size() == 2);
    ASSERT_TRUE(updatedQuestion.options().back().positionedAt()  == 2);
    ASSERT_TRUE(updatedQuestion.options().front().positionedAt() == 1);

    /// It deletes the question putting the database in the same state it was before the test.
    allQuestions->erase(updatedQuestion);
    ASSERT_THROW(allQuestions->erase(updatedQuestion),
        Domain::Model::Poll::QuestionNotFoundException
    );

}
