#ifndef File_CORSHeadersJSONFileReader_INCLUDED
#define File_CORSHeadersJSONFileReader_INCLUDED

#include <string>
#include "Foundation/IO/AbstractJSONFileReader.h"
#include "Foundation/Application/ConfigurationFileInterface.h"

namespace File {


    class CORSHeadersJSONFileReader : public Foundation::IO::AbstractJSONFileReader
    {
    public:
        CORSHeadersJSONFileReader() = delete;
        explicit CORSHeadersJSONFileReader(std::unique_ptr<Foundation::Application::ConfigurationFileInterface>);

    };


}

#endif
