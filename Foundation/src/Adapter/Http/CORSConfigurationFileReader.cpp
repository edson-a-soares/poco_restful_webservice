#include "Adapter/Http/CORSConfigurationFileReader.h"

namespace Http {


    CORSConfigurationFileReader::CORSConfigurationFileReader(std::unique_ptr<Foundation::Application::ConfigurationFileInterface> configurationFile)
        : AbstractJsonFileReader(
            std::move(configurationFile)->path(),
            {
                "allow_origins",
                "allow_http_methods",
                "allow_http_headers",
                "allow_credentials",
                "allow_credentials"
            }
        )
    {}


}
