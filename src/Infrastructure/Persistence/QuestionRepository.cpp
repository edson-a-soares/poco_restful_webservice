#include "Infrastructure/Persistence/QuestionRepository.h"

#include "Poco/SQL/RecordSet.h"
#include "Poco/SQL/SessionFactory.h"
#include "Poco/SQL/MySQL/Connector.h"
#include "Poco/SQL/MySQL/MySQLException.h"
#include "Infrastructure/Persistence/TableGateway.h"
#include "Domain/Model/Poll/QuestionNotFoundException.h"
#include "Infrastructure/Persistence/OptionTableGateway.h"

namespace Infrastructure {
namespace Persistence {


    QuestionRepository::QuestionRepository(Poco::SQL::Session & session)
        : _session(session)
    { }

    QuestionRepository::~QuestionRepository()
    {
        if ( _session.isConnected() ) {
            _session.close();
            Poco::SQL::MySQL::Connector::unregisterConnector();
        }
    }

    void QuestionRepository::store(const Domain::Model::Poll::Question & question)
    {

        TableGateway tableGateway(_session);
        OptionTableGateway optionTableGateway(_session);
        try {

            _session.begin();

            tableGateway
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

            auto options = question.options();
            for ( auto const & option : options )
                optionTableGateway.store(question.identity(), option);

            _session.commit();

        } catch (Poco::Exception & exception) {
            _session.rollback();
            throw exception;
        }

    }

    void QuestionRepository::update(const Domain::Model::Poll::Question & question)
    {

        TableGateway tableGateway(_session);
        OptionTableGateway optionTableGateway(_session);
        try {

            _session.begin();

            tableGateway
                // .throwException(true)
                .table("question")
                .withColumn("question_text",   question.text())
                .withColumn("question_label",  question.label())
                .withColumn("details",         question.details())
                .withColumn("ends_at",         toString(question.endAt()))
                .withColumn("starts_at",       toString(question.startAt()))
                .withColumn("last_updated_at", toString(question.lastUpdatedAt()))
                .updateWhere("question_id",    question.identity());

            if ( !question.options().empty() )
                optionTableGateway.handleUpdate(question.identity(), question.options());

            _session.commit();

        } catch (Poco::Exception & exception) {
            _session.rollback();
            throw exception;
        }

    }

    void QuestionRepository::erase(const Domain::Model::Poll::Question & question)
    {

        TableGateway tableGateway(_session);
        try {

            _session.begin();

            tableGateway
                .throwException(true)
                .table("question")
                .removeWhere("question_id", question.identity());

            _session.commit();

        } catch (Poco::NotFoundException & exception) {
            _session.rollback();
            throw Domain::Model::Poll::QuestionNotFoundException();
        } catch (Poco::Exception & exception) {
            _session.rollback();
            throw exception;
        }

    }

    Domain::Model::Poll::Question QuestionRepository::withIdentity(const std::string & questionId)
    {

        const int DEFAULT_ROW = 0;
        TableGateway tableGateway(_session);
        OptionTableGateway optionTableGateway(_session);
        try {

            Poco::SQL::RecordSet recordSet =
                tableGateway
                    .table("question")
                    .selectWhere("question_id", questionId);

            std::size_t rows = recordSet.rowCount();
            if ( rows == 0 )
                throw Domain::Model::Poll::QuestionNotFoundException(questionId);

            Domain::Model::Poll::Question retrievedQuestion{
                recordSet.value("question_id",            DEFAULT_ROW).toString(),
                optionTableGateway.findOptions(questionId),
                toDate(recordSet.value("created_at",      DEFAULT_ROW).toString()),
                toDate(recordSet.value("last_updated_at", DEFAULT_ROW).toString()),
                toDate(recordSet.value("starts_at",       DEFAULT_ROW).toString()),
                toDate(recordSet.value("ends_at",         DEFAULT_ROW).toString())
            };

            retrievedQuestion.withDetails(recordSet.value("details",        DEFAULT_ROW).toString());
            retrievedQuestion.withText(   recordSet.value("question_text",  DEFAULT_ROW).toString());
            retrievedQuestion.withLabel(  recordSet.value("question_label", DEFAULT_ROW).toString());

            return retrievedQuestion;

        } catch (Poco::Exception & exception) {
            throw exception;
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


} }
