#include "Poco/Data/RecordSet.h"
#include "Foundation/Domain/Model/Identity.h"
#include "Adapter/Database/QuestionRepository.h"
#include "Poll/Domain/QuestionNotFoundException.h"

namespace Database {


    QuestionRepository::QuestionRepository(std::unique_ptr<Foundation::Persistence::Database::DataAccessManagerInterface> manager)
        : dataAccessManager(std::move(manager))
    {}

    void QuestionRepository::add(const Poll::Domain::Model::Question & question)
    {
        auto tableGateway = dataAccessManager->tableGateway();
        try {
            dataAccessManager->session().begin();
            (*tableGateway)
                .table("question")
                .withColumn("question_text",    question.text())
                .withColumn("question_label",   question.label())
                .withColumn("details",          question.details())
                .withColumn("question_id",      question.identity())
                .withColumn("ends_at",          toString(question.endAt()))
                .withColumn("starts_at",        toString(question.startAt()))
                .withColumn("created_at",       toString(question.createdAt()))
                .withColumn("last_updated_at",  toString(question.lastUpdatedAt()))
                .insert();

            dataAccessManager->session().commit();

        } catch (Poco::IllegalStateException &) {
            dataAccessManager->session().rollback();
            throw;
        } catch (Poco::Exception &) {
            dataAccessManager->session().rollback();
            throw;
        }
    }

    void QuestionRepository::remove(const Poll::Domain::Model::Question & question)
    {
        auto tableGateway = dataAccessManager->tableGateway();
        try {
            dataAccessManager->session().begin();
            (*tableGateway)
                .throwException(true)
                .table("question")
                .removeWhere("question_id", question.identity());

            dataAccessManager->session().commit();

        } catch (Poco::IllegalStateException &) {
            dataAccessManager->session().rollback();
            throw;
        } catch (Poco::Exception &) {
            dataAccessManager->session().rollback();
            throw;
        }
    }

    Poll::Domain::Model::Question QuestionRepository::withIdentity(const std::string & questionId)
    {
        const int ROW_NUMBER = 0;
        auto questionTableGateway = dataAccessManager->tableGateway();

        try {
            Poco::Data::RecordSet recordSet =
                (*questionTableGateway)
                    .table("question")
                    .selectWhere("question_id", questionId);

            std::size_t rows = recordSet.rowCount();
            if ( rows == 0 )
                throw Poll::Domain::QuestionNotFoundException(questionId);

            Poll::Domain::Model::Question question {
                recordSet.value("question_id", ROW_NUMBER).toString(),
                toDate(recordSet.value("created_at", ROW_NUMBER).toString()),
                toDate(recordSet.value("last_updated_at", ROW_NUMBER).toString())
            };

            question.withDetails(recordSet.value("details", ROW_NUMBER).toString());
            question.withText(   recordSet.value("question_text", ROW_NUMBER).toString());
            question.withLabel(  recordSet.value("question_label", ROW_NUMBER).toString());
            question.endAt(      toDate(recordSet.value("ends_at", ROW_NUMBER).toString()));
            question.startAt(    toDate(recordSet.value("starts_at", ROW_NUMBER).toString()));

            return question;

        } catch (Poll::Domain::QuestionNotFoundException &) {
            throw;
        } catch (Poco::Exception &) {
            throw;
        }
    }

    std::string QuestionRepository::toString(const Poco::DateTime & dateTime)
    {
        return Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::SORTABLE_FORMAT);
    }

    Poco::DateTime QuestionRepository::toDate(const std::string & dateTime)
    {
        int timezone = 0;
        return Poco::DateTimeParser::parse(Poco::DateTimeFormat::SORTABLE_FORMAT, dateTime, timezone);
    }


}
