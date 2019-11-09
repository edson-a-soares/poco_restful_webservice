#include "Poco/Data/SQLite/SQLiteException.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Adapter/Database/SQLiteTableGateway.h"

namespace Database {


    SQLiteTableGateway::SQLiteTableGateway(Poco::Data::Session & session)
        : AbstractTableGateway(session),
          _session(session)
    {}

    void SQLiteTableGateway::insert()
    {
        if ( columnNames().empty() || columnValues().empty() )
            throw Poco::AssertionViolationException(
                "Query Assertion Violation",
                "Column's names and values must not be empty."
            );

        std::string columns = separateItByCommas(columnNames());
        auto singleQuotedValues = singleQuoteIt(columnValues());
        std::string values = insertInstructionValues(columnNames(), singleQuotedValues);

        try {
            Poco::Data::Statement insert(_session);
            auto sqlInstruction = Poco::format("INSERT OR REPLACE INTO %s (%s) VALUES %s;", tableName(), columns, values);

            insert << sqlInstruction;

            std::size_t affectedRows  = insert.execute();
            if ( throwException() && affectedRows == 0 )
                throw Poco::IllegalStateException("SQL INSERT Error", "The number of affected rows is wrong");

            clearColumnsData();

        } catch (Poco::IllegalStateException &) {
            /// @TODO Log message:
            throw;
        } catch (Poco::Data::SQLite::SQLiteException &) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Data::DataException &) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Exception &) {
            /// @TODO Log message.
            throw;
        }
    }


}
