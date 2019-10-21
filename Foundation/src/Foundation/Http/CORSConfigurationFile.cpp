#include "Foundation/Application/EnvironmentManager.h"
#include "Foundation/Http/CORSConfigurationFile.h"

namespace Foundation {
namespace Http {


    std::string CORSConfigurationFile::path() const
    {
        std::string filePath = std::string(APPLICATION_HOSTING_DIRECTORY_PATH) + "/production/cors.json";
        if ( Application::Environment::DEVELOPMENT == Application::EnvironmentManager::environment() ) {
            filePath = std::string(APPLICATION_HOSTING_DIRECTORY_PATH) + "development/cors.json";
        }

        return filePath;
    }


} }
