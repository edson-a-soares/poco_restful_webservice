#ifndef Foundation_Http_ErrorParserInterface_INCLUDED
#define Foundation_Http_ErrorParserInterface_INCLUDED

#include <string>

namespace Foundation {
namespace Http {


    class ErrorParserInterface
    {
    public:
        virtual std::string toJson(
            const std::string & host,
            const std::string & code,
            const std::string & path,
            const std::string & type,
            const std::string & description
        ) = 0;

    };


} }

#endif
