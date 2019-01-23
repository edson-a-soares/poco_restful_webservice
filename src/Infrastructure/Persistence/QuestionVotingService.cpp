#include "Domain/Model/Poll/QuestionNotFoundException.h"
#include "Infrastructure/Persistence/QuestionVotingService.h"

#include "Poco/SQL/MySQL/Connector.h"
#include "Poco/SQL/MySQL/MySQLException.h"

namespace Infrastructure {
namespace Persistence {


    QuestionVotingService::QuestionVotingService(Poco::SQL::Session & session)
        : _session(session)
    { }

    QuestionVotingService::~QuestionVotingService()
    {
        if ( _session.isConnected() ) {
            _session.close();
            Poco::SQL::MySQL::Connector::unregisterConnector();
        }
    }

    void QuestionVotingService::voteOn(const Domain::Model::Poll::Question & question,
                                       const Domain::Model::Poll::Vote & vote)
    {

        TableGateway tableGateway(_session);
        try {

            tableGateway
                .throwException(true)
                .table("question_vote")
                .withColumn("question_id", question.identity())
                .withColumn("option_id",   vote.optionIdentity())
                .withColumn("created_at",  Poco::DateTimeFormatter::format(vote.createdAt(),
                                                                       Poco::DateTimeFormat::SORTABLE_FORMAT))
                .insert();

        } catch (Poco::Exception & exception) {
            throw exception;
        }

    }

    std::list<Domain::Model::Poll::Vote> QuestionVotingService::votesFor(const Domain::Model::Poll::Question & question)
    {

        TableGateway tableGateway(_session);
        try {

            Poco::SQL::RecordSet recordSet =
                tableGateway
                    .table("question_vote")
                    .withColumn("option_id")
                    .withColumn("created_at")
                    .selectWhere("question_id", question.identity());

            int timezone = 0;
            std::size_t rows = recordSet.rowCount();
            std::list<Domain::Model::Poll::Vote> votesCollection;

            for ( std::size_t row = 0; row < rows; ++row ) {

                auto newVote = Domain::Model::Poll::Vote {
                    recordSet.value("option_id", row).toString(),
                    Poco::DateTimeParser::parse(
                        Poco::DateTimeFormat::SORTABLE_FORMAT, recordSet.value("created_at", row).toString(), timezone
                    )
                };

                votesCollection.emplace_back(newVote);

            }

            return votesCollection;

        } catch (Poco::Exception & exception) {
            throw exception;
        }

    }


} }
