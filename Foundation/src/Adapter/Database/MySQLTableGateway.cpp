#include "Poco/Data/MySQL/Connector.h"
#include "Adapter/Database/MySQLTableGateway.h"

namespace Database {


    MySQLTableGateway::MySQLTableGateway(Poco::Data::Session & session)
        : AbstractTableGateway(session)
    {}


}
