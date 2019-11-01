#include "Adapter/Http/CORSConfiguration.h"
#include "Foundation/Http/CORSConfigurationFile.h"
#include "Adapter/Http/CORSConfigurationFileReader.h"
#include "Foundation/Http/CORSConfigurationFactory.h"

namespace Foundation {
namespace Http {


    std::unique_ptr<Foundation::Http::CORSConfigurationInterface> CORSConfigurationFactory::create()
    {
        return std::make_unique<::Http::CORSConfiguration>(
            std::make_unique<::Http::CORSConfigurationFileReader>(
                std::make_unique<Foundation::Http::CORSConfigurationFile>()
            )
        );
    }


} }
