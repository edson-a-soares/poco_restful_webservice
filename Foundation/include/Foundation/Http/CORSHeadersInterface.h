#ifndef Foundation_Http_CORSHeadersInterface_INCLUDED
#define Foundation_Http_CORSHeadersInterface_INCLUDED

#include <map>
#include <string>

namespace Foundation {
namespace Http {


    class CORSHeadersInterface
    {
    public:
        virtual ~CORSHeadersInterface() = default;
        virtual std::map<std::string, std::string> headers() = 0;

    };


} }

#endif
