#include "Infrastructure/Persistence/TableGateway.h"

#include "Poco/SQL/SessionFactory.h"
#include "Poco/SQL/MySQL/Connector.h"
#include "Poco/SQL/MySQL/MySQLException.h"

using namespace Poco::SQL::Keywords;

namespace Infrastructure {
namespace Persistence {


    TableGateway::TableGateway(Poco::SQL::Session & session)
        : _table(),
          _throwException(false),
          _session(session),
          _columns(),
          _columnsValues()
    { }

    ITableGateway & TableGateway::throwException(bool flag)
    {
        _throwException = flag;
        return *this;
    }

    ITableGateway & TableGateway::table(const std::string & name)
    {
        _table = name;
        return *this;
    }

    void TableGateway::removeWhere(const std::string & whereField, const std::string & whereValue)
    {

        try {

            Poco::SQL::Statement remove(_session);

            /// Poco::SQL::Statement does not accept temporary variables.
            /// Therefore this copy from this parameter must be created.
            std::string localValue = whereValue;

            remove << "DELETE FROM %s WHERE %s = ?", _table, whereField,
                    use(localValue);

            std::size_t affectedRows = remove.execute();
            if ( _throwException && affectedRows == 0 )
                throw Poco::NotFoundException("Not Found", 400);

        } catch (Poco::SQL::ConnectionFailedException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::SQL::MySQL::StatementException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::NotFoundException & exception) {
            exception.rethrow();
        } catch (Poco::Exception & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        }

    }

    Poco::SQL::RecordSet TableGateway::selectWhere(const std::string & whereField, const std::string & whereValue)
    {

        try {

            Poco::SQL::Statement select(_session);

            /// Poco::SQL::Statement does not accept temporary variables.
            /// Therefore these copies from these parameters must be created.
            std::string localValue = whereValue;
            std::string selectedColumns = queryColumns();

            select << "SELECT %s FROM %s WHERE %s = ?", selectedColumns, _table, whereField,
                    use(localValue), now;

            return Poco::SQL::RecordSet(select);

        } catch (Poco::SQL::ConnectionFailedException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::SQL::MySQL::StatementException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::Exception & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        }

    }

    void TableGateway::updateWhere(const std::string & whereField, const std::string & whereValue)
    {

        std::string fields;
        if ( _columnsValues.empty() )
            throw Poco::InvalidArgumentException("Command Columns Missing", 403);

        for ( auto const & pair : _columnsValues ) {

            if ( fields.empty() ) {
                fields += pair.first + " = '" + pair.second + "'";
                continue;
            }

            fields += ", " + pair.first + " = '" + pair.second + "'";

        }

        try {

            Poco::SQL::Statement update(_session);

            /// Poco::SQL::Statement does not accept temporary variables.
            /// Therefore these copies from these parameters must be created.
            std::string localValue = whereValue;

            update << "UPDATE %s SET %s WHERE %s = ?", _table, fields, whereField,
                    use(localValue);

            std::size_t affectedRows = update.execute();
            if ( _throwException && affectedRows == 0 )
                throw Poco::ApplicationException("SQL UPDATE Statement Not Performed", 500);

        } catch (Poco::ApplicationException & exception) {
            /// @TODO Log message: Poco::format("UPDATE %s SET %s WHERE %s = %s", _table, fields, whereField, localValue).
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::SQL::ConnectionFailedException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::SQL::MySQL::StatementException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::Exception & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        }

    }

    void TableGateway::insert()
    {

        std::string fields;
        std::string values;
        if ( _columnsValues.empty() )
            throw Poco::InvalidArgumentException("Command Columns Missing", 403);

        for ( auto pair = _columnsValues.begin(); pair != _columnsValues.end(); ++pair ) {

            if ( fields.empty() ) {
                fields += pair->first;
                values += "'" + pair->second + "'";
                continue;
            }

            /// Let the last pair for getting collected out of the loop.
            if ( pair == --_columnsValues.end() )
                break;

            fields += ", " + pair->first;
            values += ", '" + pair->second + "'";

        }

        auto lastPair = --_columnsValues.end();

        std::string lastField = lastPair->first;
        std::string lastValue = lastPair->second;

        try {

            Poco::SQL::Statement insert(_session);

            insert << "INSERT INTO %s (%s, %s) VALUES (%s, ?)", _table, fields, lastField, values,
                    use(lastValue);

            std::size_t affectedRows = insert.execute();
            if ( _throwException && affectedRows == 0 )
                throw Poco::ApplicationException("SQL INSERT Statement Not Performed", 500);

            _columnsValues.clear();

        } catch (Poco::ApplicationException & exception) {
            /// @TODO Log message:
            /// Poco::format("INSERT INTO %s (%s, %s) VALUES (%s, %s)", _table, fields, lastField, values, lastValue)
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::SQL::ConnectionFailedException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::SQL::MySQL::StatementException & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        } catch (Poco::Exception & exception) {
            /// @TODO Log message.
            throw Poco::Exception("Internal Server Error", 500);
        }

    }

    ITableGateway & TableGateway::withColumn(const std::string & name)
    {
        _columns.push_back(name);
        return *this;
    }

    ITableGateway & TableGateway::withColumn(const std::string & column, const std::string & value)
    {
        _columnsValues[column] = value;
        return *this;
    }

    std::string TableGateway::queryColumns() const
    {

        std::string columns;
        if ( _columns.empty() )
            columns = "*";

        for ( auto iterator = _columns.begin(); iterator != _columns.end(); ++iterator ) {

            columns += *iterator;
            if ( iterator != --_columns.end() )
                columns += ", ";

        }

        return columns;

    }


} }
