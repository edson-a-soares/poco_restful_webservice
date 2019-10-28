#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/Exception.h"
#include "Foundation/Application/EnvironmentManager.h"
#include "Foundation/Application/AbstractConfiguration.h"

namespace Foundation {
namespace Application {


    AbstractConfiguration::AbstractConfiguration(std::string fileName)
        : _basePath(APPLICATION_HOSTING_DIRECTORY_PATH),
          _fileName(std::move(fileName))
    {}

    std::string AbstractConfiguration::path() const
    {
        std::string filePath = _basePath + "/data/settings/" + _fileName;
        try {
            if ( Application::Environment::PRODUCTION == Application::EnvironmentManager::environment() )
                filePath = _basePath + "/production/" + _fileName;

            if ( Application::Environment::DEVELOPMENT == Application::EnvironmentManager::environment() )
                filePath = _basePath + "/development/" + _fileName;

        } catch (Poco::NotFoundException & exception) {
            Poco::Logger & logger = Poco::Logger::get("TestLogger");
            logger.fatal(exception.message());

            Poco::File configurationFile = Poco::File(filePath);
            if ( !configurationFile.exists() || !configurationFile.isFile() ) {
                logger.information(
                    "Using local data/settings as application critical support. "
                    "Configuration file " + _fileName + " being used is " + filePath
                );
                throw;
            }
        }

        return filePath;
    }


} }
