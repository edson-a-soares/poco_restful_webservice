#ifndef UnitTests_Http_Context_FakeCORSConfigurationFile_INCLUDED
#define UnitTests_Http_Context_FakeCORSConfigurationFile_INCLUDED

#include "Foundation/Application/AbstractConfigurationFile.h"

namespace UnitTests {
namespace File {
namespace Context {


    class FakeCORSConfigurationFile : public Foundation::Application::AbstractConfigurationFile
    {
    public:
        FakeCORSConfigurationFile()
            : AbstractConfigurationFile("settings/cors.json")
        {
            basePath(TESTS_DATA_PATH);
        }

    };


} } }

#endif
