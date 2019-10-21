#ifndef Foundation_Application_ConfigurationFileInterface_INCLUDED
#define Foundation_Application_ConfigurationFileInterface_INCLUDED

#include <string>

namespace Foundation {
namespace Application {


    class ConfigurationFileInterface
    {
    public:
        virtual ~ConfigurationFileInterface() = default;
        virtual std::string path() const = 0;

    };


} }

#endif
