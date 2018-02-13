#include "Infrastructure/Persistence/ConnectionManager.h"

#include "Poco/Data/SessionFactory.h"
#include "Poco/Data/MySQL/Connector.h"
#include "Poco/Data/MySQL/MySQLException.h"

namespace Infrastructure {
namespace Persistence {


    Poco::Data::Session ConnectionManager::getSession()
    {
        const std::string user="developer";
        const std::string password="abc12345";
        const std::string host="192.168.1.100";
        const std::string db="poco_webservice_schema";

        std::string connectionString = "host=" + host + "; user=" + user + "; password=" + password +"; db=" + db;
        return Poco::Data::SessionFactory::instance().create(Poco::Data::MySQL::Connector::KEY, connectionString);
    }


} }
