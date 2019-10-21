#ifndef UnitTests_Http_Context_FakeAbstractFactory_INCLUDED
#define UnitTests_Http_Context_FakeAbstractFactory_INCLUDED

#include <string>
#include "Adapter/Http/Context/FakeResourceFactory.h"
#include "Foundation/Http/RouterAbstractFactoryInterface.h"

namespace UnitTests {
namespace Http {
namespace Context {


    class FakeAbstractFactory : public Foundation::Http::RouterAbstractFactoryInterface
    {
    public:
    	~FakeAbstractFactory() override = default;
        std::unique_ptr<Foundation::Http::ResourceFactoryInterface> createResourceFactory(const std::string & resourceName) override;

    };


    inline std::unique_ptr<Foundation::Http::ResourceFactoryInterface> FakeAbstractFactory::createResourceFactory(const std::string & resourceName)
    {
        std::unique_ptr<Foundation::Http::ResourceFactoryInterface> resourceFactory = nullptr;

        if ( resourceName == "Resource::FakeActualResource" )
            resourceFactory = std::make_unique<UnitTests::Http::Context::FakeResourceFactory>();

        return resourceFactory;
    }


} } }

#endif
