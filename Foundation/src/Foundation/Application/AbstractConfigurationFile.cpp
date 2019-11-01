#include "Poco/File.h"
#include "Poco/Logger.h"
#include "Poco/Exception.h"
#include "Foundation/Application/EnvironmentManager.h"
#include "Foundation/Application/AbstractConfigurationFile.h"

namespace Foundation {
namespace Application {


    AbstractConfigurationFile::AbstractConfigurationFile(const std::string & fileName)
        : _basePath(APPLICATION_HOSTING_DIRECTORY_PATH),
          _fileName(fileName)
    {}

    void AbstractConfigurationFile::basePath(const std::string & path)
    {
        _basePath = path;
    }

    std::string AbstractConfigurationFile::path() const
    {
        std::string filePath = _basePath + _fileName;
        auto environment     = Application::EnvironmentManager::environment();
        try {
            if ( Application::DEBUG == environment && _basePath == APPLICATION_HOSTING_DIRECTORY_PATH)
                filePath = _basePath + "/data/settings/" + _fileName;

            if ( Application::PRODUCTION == environment )
                filePath = _basePath + "/production/" + _fileName;

            if ( Application::DEVELOPMENT == environment )
                filePath = _basePath + "/development/" + _fileName;

        } catch (Poco::NotFoundException & exception) {

            Poco::Logger & logger = Poco::Logger::get("TestLogger");
            logger.critical(exception.message());
            logger.information("Configuration file " + _fileName + " being used is " + filePath);

            Poco::File configurationFile = Poco::File(filePath);
            poco_assert_dbg( configurationFile.exists() && configurationFile.isFile());
            if ( !configurationFile.exists() || !configurationFile.isFile() )
                throw;

        }

        return filePath;
    }


} }
