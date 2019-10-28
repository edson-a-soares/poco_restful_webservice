#include "Poco/String.h"
#include "Poco/Exception.h"
#include "Poco/Environment.h"
#include "Foundation/Application/EnvironmentManager.h"

namespace Foundation {
namespace Application {


	Environment EnvironmentManager::environment()
    {
        if ( !Poco::Environment::has("POCO_WEBSERVICE_ENVIRONMENT") )
            throw Poco::NotFoundException("Environment Variable Not Available", "Environment variable POCO_WEBSERVICE_ENVIRONMENT has not been set.");

        Environment environment = Environment::DEBUG;
		if ( Poco::toLower(Poco::Environment::get("POCO_WEBSERVICE_ENVIRONMENT")) == "production" )
        	environment = Environment::PRODUCTION;

		if (Poco::toLower(Poco::Environment::get("POCO_WEBSERVICE_ENVIRONMENT")) == "development")
            environment = Environment::DEVELOPMENT;

	    return environment;
    }


} }
