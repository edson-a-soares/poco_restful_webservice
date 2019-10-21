#ifndef File_CORSHeadersFactory_INCLUDED
#define File_CORSHeadersFactory_INCLUDED

#include <memory>
#include "Foundation/Http/CORSHeadersInterface.h"

namespace Foundation {
namespace Http {


    class CORSHeadersFactory
    {
    public:
        CORSHeadersFactory()  = delete;
        ~CORSHeadersFactory() = delete;
        static std::unique_ptr<Foundation::Http::CORSHeadersInterface> create();

    };


} }

#endif
