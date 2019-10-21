#ifndef File_CORSHeadersHandler_INCLUDED
#define File_CORSHeadersHandler_INCLUDED

#include <map>
#include <string>
#include <memory>
#include "Foundation/Http/CORSHeadersInterface.h"
#include "Foundation/IO/JSONFileReaderInterface.h"

namespace File {


    class CORSHeadersFromJSONFile :
        public Foundation::Http::CORSHeadersInterface
    {
    public:
        explicit CORSHeadersFromJSONFile(std::unique_ptr<Foundation::IO::JSONFileReaderInterface>);
        std::map<std::string, std::string> headers() override;

    private:
        std::map<std::string, std::string> _headers;
        std::unique_ptr<Foundation::IO::JSONFileReaderInterface> _fileReader;

    };


}

#endif
