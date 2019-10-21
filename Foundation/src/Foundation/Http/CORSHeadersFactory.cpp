#include "Adapter/File/CORSHeadersFromJSONFile.h"
#include "Foundation/Http/CORSHeadersFactory.h"
#include "Foundation/Http/CORSConfigurationFile.h"
#include "Adapter/File/CORSHeadersJSONFileReader.h"

namespace Foundation {
namespace Http {


    std::unique_ptr<Foundation::Http::CORSHeadersInterface> CORSHeadersFactory::create()
    {
        return std::make_unique<File::CORSHeadersFromJSONFile>(
            std::make_unique<File::CORSHeadersJSONFileReader>(
                std::make_unique<Foundation::Http::CORSConfigurationFile>()
            )
        );
    }


} }
