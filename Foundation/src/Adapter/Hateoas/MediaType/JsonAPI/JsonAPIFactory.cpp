#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIFactory.h"
#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIErrorBuilder.h"
#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIResourceBuilder.h"
#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIResourceCollectionBuilder.h"

namespace Hateoas {


    std::unique_ptr<Foundation::Hateoas::ErrorBuilderInterface> JsonAPIFactory::error()
    {
        return std::make_unique<JsonAPIErrorBuilder>();
    }

    std::unique_ptr<Foundation::Hateoas::ResourceBuilderInterface> JsonAPIFactory::resource()
    {
        return std::make_unique<JsonAPIResourceBuilder>();
    }

    std::unique_ptr<Foundation::Hateoas::ResourceCollectionBuilderInterface> JsonAPIFactory::collection()
    {
        return std::make_unique<JsonAPIResourceCollectionBuilder>();
    }


}
