#ifndef UnitTests_Http_Context_FakeResourceFactory_INCLUDED
#define UnitTests_Http_Context_FakeResourceFactory_INCLUDED

#include "Adapter/Http/Context/FakeActualResource.h"
#include "Foundation/Http/ResourceFactoryInterface.h"

namespace UnitTests {
namespace Http {
namespace Context {


    class FakeResourceFactory : public Foundation::Http::ResourceFactoryInterface
    {
    public:
        ~FakeResourceFactory() override = default;
        Poco::Net::HTTPRequestHandler * createResource() override;

    };


    inline Poco::Net::HTTPRequestHandler * FakeResourceFactory::createResource()
    {
        return new UnitTests::Http::Context::FakeActualResource();
    }


} } }

#endif
