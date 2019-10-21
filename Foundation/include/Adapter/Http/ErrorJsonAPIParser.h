#ifndef Http_ErrorJSONParser_INCLUDED
#define Http_ErrorJSONParser_INCLUDED

#include <string>
#include "Foundation/Http/ErrorParserInterface.h"

namespace Http {


    class ErrorJsonAPIParser : public Foundation::Http::ErrorParserInterface
    {
    public:
        std::string toJson(
            const std::string & host,
            const std::string & code,
            const std::string & path,
            const std::string & type,
            const std::string & description
        ) override;

    };


}

#endif
