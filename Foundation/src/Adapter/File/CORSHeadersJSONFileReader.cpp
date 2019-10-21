#include "Adapter/File/CORSHeadersJSONFileReader.h"

namespace File {


    CORSHeadersJSONFileReader::CORSHeadersJSONFileReader(std::unique_ptr<Foundation::Application::ConfigurationFileInterface> configurationFile)
        : AbstractJSONFileReader(
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
