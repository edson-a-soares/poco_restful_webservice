#include "Foundation/Hateoas/MediaTypeFactory.h"
#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIFactory.h"

namespace Foundation {
namespace Hateoas {


    std::unique_ptr<MediaTypeAbstractFactoryInterface> MediaTypeFactory::create(MediaType adapter)
    {
        switch (adapter) {
            case MediaType::JSON_API:
                return std::make_unique<::Hateoas::JsonAPIFactory>();
        }
    }


} }
