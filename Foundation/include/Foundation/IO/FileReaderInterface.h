#ifndef Foundation_IO_FileReaderInterface_INCLUDED
#define Foundation_IO_FileReaderInterface_INCLUDED

#include <string>

namespace Foundation {
namespace IO {


    class FileReaderInterface
    {
    public:
        virtual ~FileReaderInterface()= default;
        virtual std::string read() = 0;

    };


} }

#endif
