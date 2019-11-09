#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/MySQL/MySQLException.h"
#include "Adapter/Database/AbstractTableGateway.h"

using namespace Poco::Data::Keywords;

namespace Database {


    AbstractTableGateway::AbstractTableGateway(Poco::Data::Session & session)
        : _throwException(false),
          _tableName(),
          _session(session),
          _columnNames(),
          _columnValues()
    {}


    void AbstractTableGateway::insert()
    {
        if ( columnNames().empty() || columnValues().empty() )
            throw Poco::AssertionViolationException(
                    "Query Assertion Violation",
                    "Column's names and values must not be empty."
            );

        std::string columns               = separateItByCommas(columnNames());
        std::string conflictUpdateClause  = columnConflictClauseFormat(columnNames());

        auto singleQuotedValues = singleQuoteIt(columnValues());
        std::string values = insertInstructionValues(columnNames(), singleQuotedValues);

        try {
            Poco::Data::Statement insert(_session);
            auto sqlInstruction = Poco::format("INSERT INTO %s (%s) VALUES %s ON DUPLICATE KEY UPDATE %s;",
                tableName(),
                columns,
                values,
                conflictUpdateClause
            );

            insert << sqlInstruction;

            std::size_t affectedRows  = insert.execute();
            if ( throwException() && affectedRows == 0 )
                throw Poco::IllegalStateException();

            clearColumnsData();

        } catch (Poco::IllegalStateException & exception) {
            /// @TODO Log message:
            throw;
        } catch (Poco::Data::ConnectionFailedException & exception) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Data::MySQL::StatementException & exception) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Exception & exception) {
            /// @TODO Log message.
            throw;
        }
    }

    Persistence::TableGatewayInterface & AbstractTableGateway::throwException(bool flag)
    {
        _throwException = flag;
        return *this;
    }

    Persistence::TableGatewayInterface & AbstractTableGateway::table(const std::string & name)
    {
        _tableName = name;
        return *this;
    }

    Persistence::TableGatewayInterface & AbstractTableGateway::withValue(const std::string & data)
    {
        _columnValues.push_back(data);
        return *this;
    }

    Persistence::TableGatewayInterface & AbstractTableGateway::withColumn(const std::string & name)
    {
        _columnNames.push_back(name);
        return *this;
    }

    Persistence::TableGatewayInterface & AbstractTableGateway::withColumn(const std::string & column, const std::string & value)
    {
        _columnNames.push_back(column);
        _columnValues.push_back(value);
        return *this;
    }

    Poco::Data::RecordSet AbstractTableGateway::selectWhere(const std::string & column, const std::string & whereValue)
    {
        try {
            Poco::Data::Statement select(_session);

            auto sqlInstruction = Poco::format("SELECT %s FROM %s WHERE %s = '%s';",
                selectQueryColumns(),
                tableName(),
                column,
                whereValue
            );

            select << sqlInstruction, now;

            return Poco::Data::RecordSet(select);

        } catch (Poco::Data::ConnectionFailedException & exception) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Data::MySQL::StatementException & exception) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Exception & exception) {
            /// @TODO Log message.
            throw;
        }
    }

    void AbstractTableGateway::removeWhere(const std::string & column, const std::string & whereValue)
    {
        try {
            Poco::Data::Statement remove(_session);
            auto sqlInstruction = Poco::format("DELETE FROM %s WHERE %s = '%s';", tableName(), column, whereValue);

            remove << sqlInstruction;

            std::size_t affectedRows = remove.execute();
            if ( _throwException && affectedRows == 0 )
                throw Poco::IllegalStateException();

        } catch (Poco::Data::ConnectionFailedException &) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Data::MySQL::StatementException &) {
            /// @TODO Log message.
            throw;
        } catch (Poco::IllegalStateException &) {
            throw;
        } catch (Poco::Exception &) {
            /// @TODO Log message.
            throw;
        }
    }

    void AbstractTableGateway::removeWhere(const std::string & whereField, const std::list<std::string> & whereValues)
    {
        auto singleQuotedValues   = singleQuoteIt(whereValues);
        auto commaSeparatedValues = separateItByCommas(singleQuotedValues);

        try {
            Poco::Data::Statement remove(_session);
            auto sqlInstruction = Poco::format("DELETE FROM %s WHERE %s IN (%s);",
                tableName(),
                whereField,
                commaSeparatedValues
            );

            remove << sqlInstruction;

            std::size_t affectedRows = remove.execute();
            if ( _throwException && affectedRows != whereValues.size() )
                throw Poco::IllegalStateException();

        } catch (Poco::Data::ConnectionFailedException &) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Data::MySQL::StatementException &) {
            /// @TODO Log message.
            throw;
        } catch (Poco::Exception &) {
            /// @TODO Log message.
            throw;
        }
    }

    std::string AbstractTableGateway::selectQueryColumns() const
    {
        std::string columns;
        if ( _columnNames.empty() )
            columns = "*";

        for ( auto iterator = _columnNames.begin(); iterator != _columnNames.end(); ++iterator ) {

            columns += *iterator;
            if ( iterator != --_columnNames.end() )
                columns += ", ";

        }

        return columns;
    }

    std::string AbstractTableGateway::insertInstructionValues(const std::list<std::string> & columnNames, const std::list<std::string> & columnValues)
    {
        if ( columnNames.empty() || columnValues.empty() )
            throw Poco::InvalidArgumentException("SQL Bad Format", "VALUES clause cannot be empty in the INSERT clause");

        std::ostringstream allValueClauses;
        int numberOfColumns = columnNames.size();
        int numberOfItems   = columnValues.size();

        for (auto i = 0; i < (numberOfItems - numberOfColumns); i += numberOfColumns)
        {
            auto begin = std::next(columnValues.begin(), i);
            auto end   = std::next(begin, numberOfColumns);

            std::list<std::string> subquery = { begin, end };
            auto valuesGroup = separateItByCommas(subquery);
            allValueClauses << "(" << valuesGroup << "), ";
        }

        auto begin = std::prev(columnValues.end(), numberOfColumns);

        std::list<std::string> lastSubquery = { begin, columnValues.end() };
        auto unitAsString = separateItByCommas(lastSubquery);
        allValueClauses << "(" << unitAsString << ")";

        return allValueClauses.str();
    }

    std::list<std::string> AbstractTableGateway::singleQuoteIt(const std::list<std::string> & list)
    {
        std::list<std::string> result;
        std::for_each(list.begin(), list.end(),
            [&result](const std::string & element) {
                auto quoted = Poco::format("'%s'", element);
                result.emplace_back(quoted);
            }
        );

        return result;
    }

    std::string AbstractTableGateway::separateItByCommas(const std::list<std::string> & list) const
    {
        std::ostringstream commaSeparatedData;
        std::copy(
            list.begin(),
            --list.end(),
            std::ostream_iterator<std::string>(commaSeparatedData, ", ")
        );
        commaSeparatedData << list.back();

        return commaSeparatedData.str();
    }

    std::string AbstractTableGateway::columnConflictClauseFormat(const std::list<std::string> & columns) const
    {
        std::ostringstream result;
        std::for_each(columns.begin(), --columns.end(),
        [&result](const std::string & columnName) {
                result << columnName << "=values(" << columnName << "), ";
            }
        );

        auto lastItem = columns.back();
        result << lastItem << "=values(" << lastItem << ")";

        return result.str();
    }

    bool AbstractTableGateway::throwException()
    {
        return _throwException;
    }

    void AbstractTableGateway::clearColumnsData()
    {
        _columnNames.clear();
        _columnValues.clear();
    }

    std::string AbstractTableGateway::tableName()
    {
        return _tableName;
    }

    std::list<std::string> AbstractTableGateway::columnNames()
    {
        return _columnNames;
    }

    std::list<std::string> AbstractTableGateway::columnValues()
    {
        return _columnValues;
    }


}
