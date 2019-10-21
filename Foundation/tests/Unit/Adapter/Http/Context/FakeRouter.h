#ifndef UnitTests_Http_Context_FakeRouter_INCLUDED
#define UnitTests_Http_Context_FakeRouter_INCLUDED

#include "Foundation/Http/Router.h"
#include "Adapter/Http/Context/FakeNotFoundError.h"
#include "Adapter/Http/Context/FakeAbstractFactory.h"
#include "Foundation/Http/RouterAbstractFactoryInterface.h"

namespace UnitTests {
namespace Http {
namespace Context {


    class FakeRouter : public Foundation::Http::Router
    {
    public:
        void loadEndpoints() override;
        Poco::Net::HTTPRequestHandler * notFoundErrorHandler() final;
        std::unique_ptr<Foundation::Http::RouterAbstractFactoryInterface> getAbstractFactory() override;

    };


    Poco::Net::HTTPRequestHandler* FakeRouter::notFoundErrorHandler()
    {
        return new UnitTests::Http::Context::FakeNotFoundError();
    }

    inline void FakeRouter::loadEndpoints()
    {
        addEndpoint("/testing_endpoint", "Resource::FakeActualResource");
    }

    inline std::unique_ptr<Foundation::Http::RouterAbstractFactoryInterface> FakeRouter::getAbstractFactory()
    {
        return std::make_unique<UnitTests::Http::Context::FakeAbstractFactory>();
    }


} } }

#endif
