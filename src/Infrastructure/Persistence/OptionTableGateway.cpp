#include "Infrastructure/Persistence/OptionTableGateway.h"
#include "Infrastructure/Persistence/TableGateway.h"

namespace Infrastructure {
namespace Persistence {


    OptionTableGateway::OptionTableGateway(Poco::SQL::Session & session)
        : _session(session)
    { }

    std::list<Domain::Model::Poll::Option> OptionTableGateway::findOptions(const std::string & questionId)
    {

        TableGateway tableGateway(_session);
        try {

            Poco::SQL::RecordSet recordSet =
                tableGateway
                    .table("question_option")
                    .withColumn("option_id")
                    .withColumn("created_at")
                    .withColumn("option_text")
                    .withColumn("last_updated_at")
                    .withColumn("position_number")
                    .selectWhere("question_id", questionId);

            std::size_t rows = recordSet.rowCount();
            std::list<Domain::Model::Poll::Option> options;

            for (std::size_t row = 0; row < rows; ++row) {

                Domain::Model::Poll::Option retrievedOption = {
                    recordSet.value("option_id", row).toString(),
                    toDate(recordSet.value("created_at", row).toString()),
                    toDate(recordSet.value("last_updated_at", row).toString())
                };

                retrievedOption.withText(  recordSet.value("option_text", row).toString());
                retrievedOption.positionAt(recordSet.value("position_number", row).convert<int>());

                options.push_back(retrievedOption);

            }

            return options;

        } catch (Poco::Exception & exception) {
            throw exception;
        }

    }

    void OptionTableGateway::handleUpdate(const std::string & questionIdentity,
                                           const std::list<Domain::Model::Poll::Option> & updatingCollection)
    {

        /// Get the current state of the collection to comparison purposes.
        auto storedCollection = findOptions(questionIdentity);

        // It goes through the stored collection comparing the stored options to the submitted ones,
        // updating the existent options and deleting the ones missing.
        for ( auto const & option : storedCollection ) {

            /// Check if the stored option is into the submitted yet.
            auto currentUpdatingOption =
                std::find_if(updatingCollection.begin(), updatingCollection.end(),
                    [option](const Domain::Model::Poll::Option & current) {
                        return option.identity() == current.identity();
                    }
                );

            /// Stored option not found into the updating collection.
            /// The option was deleted from the collection, this must be reflected in the database.
            if ( currentUpdatingOption == updatingCollection.end() )
                remove(option);
            else
                update(*currentUpdatingOption);

        }

        for ( auto const & option : updatingCollection ) {

            /// Check if the updating option is into the stored already.
            auto currentStoredOption =
                std::find_if(storedCollection.begin(), storedCollection.end(),
                    [option](const Domain::Model::Poll::Option & current) {
                        return option.identity() == current.identity();
                    }
                );

            /// Updating option not found into the stored collection.
            /// The option was created int the collection, this must be reflected in the database.
            if ( currentStoredOption == storedCollection.end() )
                store(questionIdentity, option);

        }

    }

    void OptionTableGateway::store(const std::string & questionIdentity, const Domain::Model::Poll::Option & option)
    {

        TableGateway tableGateway(_session);
        try {

            tableGateway
                .throwException(true)
                .table("question_option")
                .withColumn("option_text",     option.text())
                .withColumn("question_id",     questionIdentity)
                .withColumn("option_id",       option.identity())
                .withColumn("created_at",      toString(option.createdAt()))
                .withColumn("last_updated_at", toString(option.lastUpdatedAt()))
                .withColumn("position_number", std::to_string(option.positionedAt()))
                .insert();

        } catch (Poco::Exception & exception) {
            throw exception;
        }

    }

    void OptionTableGateway::update(const Domain::Model::Poll::Option & option)
    {

        TableGateway tableGateway(_session);

        tableGateway
            .table("question_option")
            .withColumn("option_text",     option.text())
            .withColumn("last_updated_at", toString(option.lastUpdatedAt()))
            .withColumn("position_number", std::to_string(option.positionedAt()))
            .updateWhere("option_id",      option.identity());

    }

    void OptionTableGateway::remove(const Domain::Model::Poll::Option & option)
    {

        TableGateway tableGateway(_session);
        try {

            tableGateway
                // .throwException(true)
                .table("question_option")
                .removeWhere("option_id", option.identity());

        } catch (Poco::NotFoundException & exception) {
            // throw Domain::Model::Poll::OptionNotFoundException();
        }

    }

    std::string OptionTableGateway::toString(const Poco::DateTime & dateTime)
    {
        return Poco::DateTimeFormatter::format(dateTime, Poco::DateTimeFormat::SORTABLE_FORMAT);
    }

    Poco::DateTime OptionTableGateway::toDate(const std::string & dateTime)
    {
        int timezone = 0;
        return Poco::DateTimeParser::parse(Poco::DateTimeFormat::SORTABLE_FORMAT, dateTime, timezone);
    }



} }
