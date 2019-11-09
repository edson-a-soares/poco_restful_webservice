#include <memory>
#include "gtest/gtest.h"
#include "Poll/Domain/Model/Option.h"
#include "Poll/Domain/Model/Question.h"
#include "Adapter/Database/OptionRepository.h"
#include "Poll/Domain/Model/QuestionIdentity.h"
#include "Adapter/Database/QuestionRepository.h"
#include "Foundation/Persistence/Database/DataAccessManagerFactory.h"

class OptionRepositoryTest : public ::testing::Test
{
protected:
    void SetUp() override
    {
        Poll::Domain::Model::Question newQuestion;
        questionIdentity = std::make_unique<Poll::Domain::Model::QuestionIdentity>(newQuestion.identity());

        auto questionRepository =
            std::make_unique<Database::QuestionRepository>(
                Foundation::Persistence::Database::DataAccessManagerFactory::create()
            );
        questionRepository->add(newQuestion);

        optionsCollection =
            std::make_unique<Database::OptionRepository>(
                Foundation::Persistence::Database::DataAccessManagerFactory::create()
            );
    }

    void TearDown() override
    {
        auto questionRepository =
            std::make_unique<Database::QuestionRepository>(
                Foundation::Persistence::Database::DataAccessManagerFactory::create()
            );

        auto question = questionRepository->withIdentity(questionIdentity->toString());
        questionRepository->remove(question);
    }

    std::unique_ptr<Poll::Domain::Model::QuestionIdentity> questionIdentity = nullptr;
    std::unique_ptr<Poll::Domain::Model::OptionRepositoryInterface> optionsCollection = nullptr;

};


TEST_F(OptionRepositoryTest, AddingOptionItem)
{

    Poll::Domain::Model::Option firstOption;
    firstOption.withText("First option.");
    firstOption.positionAt(1);
    optionsCollection->add(*questionIdentity, firstOption);

    auto allOptionsStored = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(allOptionsStored.size() == 1);

    Poll::Domain::Model::Option secondOption;
    secondOption.withText("Second option.");
    secondOption.positionAt(2);
    optionsCollection->add(*questionIdentity, secondOption);

    allOptionsStored = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(allOptionsStored.size() == 2);

    Poll::Domain::Model::Option thirdOption;
    thirdOption.withText("Third option.");
    thirdOption.positionAt(3);
    optionsCollection->add(*questionIdentity, thirdOption);

    allOptionsStored = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(allOptionsStored.size() == 3);

    Poll::Domain::Model::Option fourthOption;
    fourthOption.withText("Fourth option.");
    fourthOption.positionAt(4);
    optionsCollection->add(*questionIdentity, fourthOption);

    allOptionsStored = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(allOptionsStored.size() == 4);

    Poll::Domain::Model::Option fifthOption;
    fifthOption.withText("Fifth option.");
    fifthOption.positionAt(5);
    optionsCollection->add(*questionIdentity, fifthOption);

    allOptionsStored = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(allOptionsStored.size() == 5);

    optionsCollection->erase(allOptionsStored);

}

TEST_F(OptionRepositoryTest, AddingOptionsInBatch)
{

    std::list<Poll::Domain::Model::Option> allOptions;

    Poll::Domain::Model::Option firstOption;
    firstOption.withText("First option to the test.");
    firstOption.positionAt(1);
    allOptions.emplace_back(firstOption);

    Poll::Domain::Model::Option secondOption;
    secondOption.withText("Second option to the test.");
    secondOption.positionAt(2);
    allOptions.emplace_back(secondOption);

    Poll::Domain::Model::Option thirdOption;
    thirdOption.withText("Third option to the test.");
    thirdOption.positionAt(3);
    allOptions.emplace_back(thirdOption);

    Poll::Domain::Model::Option fourthOption;
    fourthOption.withText("Fourth option to the test.");
    fourthOption.positionAt(4);
    allOptions.emplace_back(fourthOption);

    Poll::Domain::Model::Option fifthOption;
    fifthOption.withText("Fifth option to the test.");
    fifthOption.positionAt(5);
    allOptions.emplace_back(fifthOption);

    optionsCollection->insert(*questionIdentity, allOptions);
    auto optionsStored = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(optionsStored.size() == allOptions.size());

    Poll::Domain::Model::Option sixthOption;
    sixthOption.withText("Sixth option to the test.");
    sixthOption.positionAt(6);
    allOptions.emplace_back(sixthOption);

    Poll::Domain::Model::Option seventhOption;
    seventhOption.withText("Seventh option to the test.");
    seventhOption.positionAt(7);
    allOptions.emplace_back(seventhOption);

    Poll::Domain::Model::Option eighthOption;
    eighthOption.withText("Eighth option to the test.");
    eighthOption.positionAt(8);
    allOptions.emplace_back(eighthOption);

    optionsCollection->insert(*questionIdentity, allOptions);
    auto finalStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(finalStoredOptions.size() == allOptions.size());

    optionsCollection->erase(allOptions);

}

TEST_F(OptionRepositoryTest, RemovingOptionsInBatch)
{

    std::list<Poll::Domain::Model::Option> allOptions;

    Poll::Domain::Model::Option firstOption;
    firstOption.withText("First option.");
    firstOption.positionAt(1);
    allOptions.emplace_back(firstOption);

    Poll::Domain::Model::Option secondOption;
    secondOption.withText("Second option.");
    secondOption.positionAt(2);
    allOptions.emplace_back(secondOption);

    Poll::Domain::Model::Option thirdOption;
    thirdOption.withText("Third option.");
    thirdOption.positionAt(3);
    allOptions.emplace_back(thirdOption);

    Poll::Domain::Model::Option fourthOption;
    fourthOption.withText("Fourth option.");
    fourthOption.positionAt(4);
    allOptions.emplace_back(fourthOption);

    Poll::Domain::Model::Option fifthOption;
    fifthOption.withText("Fifth option.");
    fifthOption.positionAt(5);
    allOptions.emplace_back(fifthOption);

    Poll::Domain::Model::Option sixthOption;
    sixthOption.withText("Sixth option.");
    sixthOption.positionAt(6);
    allOptions.emplace_back(sixthOption);

    Poll::Domain::Model::Option seventhOption;
    seventhOption.withText("Seventh option.");
    seventhOption.positionAt(7);
    allOptions.emplace_back(seventhOption);

    Poll::Domain::Model::Option eighthOption;
    eighthOption.withText("Eighth option.");
    eighthOption.positionAt(8);
    allOptions.emplace_back(eighthOption);

    optionsCollection->insert(*questionIdentity, allOptions);
    auto storedOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(storedOptions.size() == allOptions.size());

    optionsCollection->erase(allOptions);
    auto finalStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_EQ(finalStoredOptions.size(), 0);

}

TEST_F(OptionRepositoryTest, UpdatingOptionsInBatch) {

    std::list<Poll::Domain::Model::Option> allOptions;

    Poll::Domain::Model::Option firstOption;
    firstOption.withText("First option to the test.");
    firstOption.positionAt(1);
    allOptions.emplace_back(firstOption);

    Poll::Domain::Model::Option secondOption;
    secondOption.withText("Second option to the test.");
    secondOption.positionAt(2);
    allOptions.emplace_back(secondOption);

    optionsCollection->insert(*questionIdentity, allOptions);

    std::list<Poll::Domain::Model::Option> optionsForUpdate;

    auto optionOne(firstOption);
    optionOne.withText("Question one already updated.");
    optionOne.positionAt(2);
    optionsForUpdate.emplace_back(optionOne);

    auto optionTwo(secondOption);
    optionTwo.withText("Question two also updated.");
    optionTwo.positionAt(1);
    optionsForUpdate.emplace_back(optionTwo);

    optionsCollection->insert(*questionIdentity, optionsForUpdate);
    auto updatedOptions = optionsCollection->allWith(*questionIdentity);

    updatedOptions.sort(
        [](const Poll::Domain::Model::Option & first, const Poll::Domain::Model::Option & second) {
            return first.positionedAt() < second.positionedAt();
        }
    );

    auto optionsIterator = updatedOptions.begin();
    ASSERT_EQ(optionsIterator->positionedAt(), 1);
    ASSERT_EQ(optionsIterator->text(), "Question two also updated.");

    optionsIterator = std::next(optionsIterator, 1);
    ASSERT_EQ(optionsIterator->positionedAt(), 2);
    ASSERT_EQ(optionsIterator->text(), "Question one already updated.");

    optionsCollection->erase(allOptions);

}

TEST_F(OptionRepositoryTest, RemovingByOptionItem)
{

    std::list<Poll::Domain::Model::Option> allOptions;

    Poll::Domain::Model::Option firstOption;
    firstOption.withText("First option.");
    firstOption.positionAt(1);
    allOptions.emplace_back(firstOption);

    Poll::Domain::Model::Option secondOption;
    secondOption.withText("Second option.");
    secondOption.positionAt(2);
    allOptions.emplace_back(secondOption);

    Poll::Domain::Model::Option thirdOption;
    thirdOption.withText("Third option.");
    thirdOption.positionAt(3);
    allOptions.emplace_back(thirdOption);

    Poll::Domain::Model::Option fourthOption;
    fourthOption.withText("Fourth option.");
    fourthOption.positionAt(4);
    allOptions.emplace_back(fourthOption);

    Poll::Domain::Model::Option fifthOption;
    fifthOption.withText("Fifth option.");
    fifthOption.positionAt(5);
    allOptions.emplace_back(fifthOption);

    optionsCollection->insert(*questionIdentity, allOptions);
    auto allStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_TRUE(allStoredOptions.size() == allOptions.size());


    optionsCollection->remove(fifthOption);
    allStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_EQ(allStoredOptions.size(), allOptions.size() - 1);

    optionsCollection->remove(fourthOption);
    allStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_EQ(allStoredOptions.size(), allOptions.size() - 2);

    optionsCollection->remove(thirdOption);
    allStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_EQ(allStoredOptions.size(), allOptions.size() - 3);

    optionsCollection->remove(secondOption);
    allStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_EQ(allStoredOptions.size(), allOptions.size() - 4);

    optionsCollection->remove(firstOption);
    allStoredOptions = optionsCollection->allWith(*questionIdentity);
    ASSERT_EQ(allStoredOptions.size(), 0);

}
