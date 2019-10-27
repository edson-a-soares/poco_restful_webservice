#include "Poco/Exception.h"
#include "Foundation/Http/CORSConfigurationFile.h"
#include "Foundation/Application/EnvironmentManager.h"

namespace Foundation {
namespace Http {


    std::string CORSConfigurationFile::path() const
    {
        std::string filePath = std::string(APPLICATION_HOSTING_DIRECTORY_PATH) + "/production/cors.json";
        try {
            if ( Application::Environment::DEVELOPMENT == Application::EnvironmentManager::environment() )
                filePath = std::string(APPLICATION_HOSTING_DIRECTORY_PATH) + "/development/cors.json";
        } catch (Poco::NotFoundException & exception) {
            filePath = std::string(APPLICATION_HOSTING_DIRECTORY_PATH) + "/data/settings/cors.json";
        }

        return filePath;
    }


} }
