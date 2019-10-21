#ifndef Foundation_IO_JSONFileReaderInterface_INCLUDED
#define Foundation_IO_JSONFileReaderInterface_INCLUDED

#include <string>

namespace Foundation {
namespace IO {


    class JSONFileReaderInterface
    {
    public:
        virtual ~JSONFileReaderInterface() = default;
        virtual std::string fetch(const std::string & identifier) = 0;

    };


} }

#endif
