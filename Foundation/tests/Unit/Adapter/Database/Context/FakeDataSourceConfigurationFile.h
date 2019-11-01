#ifndef UnitTests_Database_Context_FakeDataSourceConfigurationFile_INCLUDED
#define UnitTests_Database_Context_FakeDataSourceConfigurationFile_INCLUDED

#include "Foundation/Application/AbstractConfigurationFile.h"

namespace UnitTests {
namespace Database {
namespace Context {


    class FakeDataSourceConfigurationFile : public Foundation::Application::AbstractConfigurationFile
    {
    public:
        FakeDataSourceConfigurationFile()
            : AbstractConfigurationFile("settings/datasource.json")
        {
            basePath(TESTS_DATA_PATH);
        };

    };


} } }

#endif
