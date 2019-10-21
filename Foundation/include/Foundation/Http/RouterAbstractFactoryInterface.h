#ifndef Foundation_Http_AbstractFactoryInterface_INCLUDED
#define Foundation_Http_AbstractFactoryInterface_INCLUDED

#include <string>
#include <memory>
#include "Foundation/Http/ResourceFactoryInterface.h"

namespace Foundation {
namespace Http {


    class RouterAbstractFactoryInterface
    {
    public:
    	virtual ~RouterAbstractFactoryInterface() = default;
        virtual std::unique_ptr<ResourceFactoryInterface> createResourceFactory(const std::string & resourceName) = 0;

    };


} }

#endif
