#ifndef UnitTests_File_Context_StubCORSHeadersFile_INCLUDED
#define UnitTests_File_Context_StubCORSHeadersFile_INCLUDED

#include "Foundation/Application/ConfigurationFileInterface.h"

namespace UnitTests {
namespace File {
namespace Context {


    class StubCORSHeadersFile : public Foundation::Application::ConfigurationFileInterface
    {
    public:
        StubCORSHeadersFile() : dependenciesPath(TESTS_DATA_PATH)
        {
            dependenciesPath.append("settings/cors.json");
        }
        ~StubCORSHeadersFile() override = default;
        std::string path() const override;

    private:
        std::string dependenciesPath;

    };

    inline std::string StubCORSHeadersFile::path() const
    {
        return dependenciesPath;
    }


} } }

#endif
