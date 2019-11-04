#include "Poco/Data/SQLite/Connector.h"
#include "Adapter/Database/SQLiteTableGateway.h"

namespace Database {


    SQLiteTableGateway::SQLiteTableGateway(Poco::Data::Session & session)
        : AbstractTableGateway(session)
    {}


}
