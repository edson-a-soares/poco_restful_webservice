#include "Poco/Data/RecordSet.h"
#include "Foundation/Domain/Model/Identity.h"
#include "Adapter/Database/OptionRepository.h"
#include "Poll/Domain/QuestionNotFoundException.h"

namespace Database {


    OptionRepository::OptionRepository(std::unique_ptr<Foundation::Persistence::Database::DataAccessManagerInterface> manager)
        : dataAccessManager(std::move(manager))
    {}


    void OptionRepository::remove(const Poll::Domain::Model::Option & option)
    {
        auto tableGateway = dataAccessManager->tableGateway();
        try {
            dataAccessManager->session().begin();
            (*tableGateway)
                .throwException(true)
                .table("question_option")
                .removeWhere("option_id", option.identity());

            dataAccessManager->session().commit();

        } catch (Poco::Exception &) {
            dataAccessManager->session().rollback();
        }
    }

    void OptionRepository::erase(const std::list<Poll::Domain::Model::Option> & options)
    {
        auto tableGateway = dataAccessManager->tableGateway();

        std::list<std::string> toDelete;
        std::for_each(options.begin(), options.end(),
            [&toDelete](const Poll::Domain::Model::Option & option) {
                toDelete.emplace_back(option.identity());
            }
        );

        try {
            dataAccessManager->session().begin();
            (*tableGateway)
                .throwException(true)
                .table("question_option")
                .removeWhere("option_id", toDelete);

            dataAccessManager->session().commit();

        } catch (Poco::IllegalStateException &) {
            dataAccessManager->session().rollback();
        } catch (Poco::Exception &) {
            dataAccessManager->session().rollback();
        }
    }

    Poll::Domain::Model::Option OptionRepository::withIdentity(const Poll::Domain::Model::OptionIdentity & identity)
    {
        const int ROW_NUMBER = 0;
        auto tableGateway    = dataAccessManager->tableGateway();

        try {
            Poco::Data::RecordSet recordSet =
                (*tableGateway)
                    .table("question_option")
                    .selectWhere("option_id", identity.toString());

            std::size_t rowsNumber = recordSet.rowCount();
            if ( rowsNumber == 0 )
                throw Poco::NotFoundException();

            Poll::Domain::Model::Option option = {
                recordSet.value("option_id",                      ROW_NUMBER).toString(),
                toDate(recordSet.value("created_at",      ROW_NUMBER).toString()),
                toDate(recordSet.value("last_updated_at", ROW_NUMBER).toString())
            };

            option.withText(recordSet.value("option_text",       ROW_NUMBER).toString());
            option.positionAt(recordSet.value("position_number", ROW_NUMBER).convert<int>());

            return option;

        } catch (Poco::Exception &) {
            throw;
        }
    }

    void OptionRepository::insert(const Poll::Domain::Model::QuestionIdentity & questionIdentity,
                                  const std::list<Poll::Domain::Model::Option> & allOptions)
    {
        auto tableGateway = dataAccessManager->tableGateway();

        try {
            dataAccessManager->session().begin();
            (*tableGateway)
                .table("question_option")
                .throwException(true)
                .withColumn("option_text")
                .withColumn("option_id")
                .withColumn("question_id")
                .withColumn("created_at")
                .withColumn("last_updated_at")
                .withColumn("position_number");

            for ( auto const & option : allOptions ) {
                (*tableGateway)
                    .withValue(option.text())
                    .withValue(option.identity())
                    .withValue(questionIdentity.toString())
                    .withValue(toString(option.createdAt()))
                    .withValue(toString(option.lastUpdatedAt()))
                    .withValue(std::to_string(option.positionedAt()));
            }

            tableGateway->insert();
            dataAccessManager->session().commit();

        } catch (Poco::Exception &) {
            dataAccessManager->session().rollback();
        }
    }

    void OptionRepository::add(const Poll::Domain::Model::QuestionIdentity & questionIdentity,
                               const Poll::Domain::Model::Option & option)
    {
        auto tableGateway = dataAccessManager->tableGateway();

        try {
            dataAccessManager->session().begin();
            (*tableGateway)
                .table("question_option")
                .throwException(true)
                .withColumn("option_text",      option.text())
                .withColumn("option_id",        option.identity())
                .withColumn("question_id",      questionIdentity.toString())
                .withColumn("created_at",      toString(option.createdAt()))
                .withColumn("last_updated_at", toString(option.lastUpdatedAt()))
                .withColumn("position_number",  std::to_string(option.positionedAt()));

            tableGateway->insert();
            dataAccessManager->session().commit();

        } catch (Poco::Exception &) {
            dataAccessManager->session().rollback();
        }
    }

    std::list<Poll::Domain::Model::Option> OptionRepository::allWith(const Poll::Domain::Model::QuestionIdentity & identity)
    {
        std::list<Poll::Domain::Model::Option> options;
        auto tableGateway = dataAccessManager->tableGateway();

        try {
            Poco::Data::RecordSet recordSet =
                (*tableGateway)
                    .table("question_option")
                    .withColumn("option_id")
                    .withColumn("created_at")
                    .withColumn("option_text")
                    .withColumn("last_updated_at")
                    .withColumn("position_number")
                    .selectWhere("question_id", identity.toString());

            std::size_t rowsNumber = recordSet.rowCount();
            for ( std::size_t currentRow = 0; currentRow < rowsNumber; ++currentRow) {
                Poll::Domain::Model::Option option = {
                    recordSet.value("option_id", currentRow).toString(),
                    toDate(recordSet.value("created_at", currentRow).toString()),
                    toDate(recordSet.value("last_updated_at", currentRow).toString())
                };

                option.withText(recordSet.value("option_text", currentRow).toString());
                option.positionAt(recordSet.value("position_number", currentRow).convert<int>());

                options.push_back(option);
            }

        } catch (Poco::Exception &) {
            throw;
        }

        return options;
    }

    std::string OptionRepository::toString(const Poco::DateTime & dateTime)
    {
        return Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::SORTABLE_FORMAT);
    }

    Poco::DateTime OptionRepository::toDate(const std::string & dateTime)
    {
        int timezone = 0;
        return Poco::DateTimeParser::parse(Poco::DateTimeFormat::SORTABLE_FORMAT, dateTime, timezone);
    }


}
