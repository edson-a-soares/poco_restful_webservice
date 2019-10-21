#ifndef Foundation_Http_CORSConfigurationFile_INCLUDED
#define Foundation_Http_CORSConfigurationFile_INCLUDED

#include "Foundation/Application/ConfigurationFileInterface.h"

namespace Foundation {
namespace Http {


    class CORSConfigurationFile : public Application::ConfigurationFileInterface
    {
    public:
	    std::string path() const override;

    };


} }

#endif
