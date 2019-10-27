#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIResourceBuilder.h"

namespace Hateoas {


    JsonAPIResourceBuilder::JsonAPIResourceBuilder()
        : includes(),
          relationships()
    {}

    std::string JsonAPIResourceBuilder::toString()
    {
        if ( !relationships.empty() )
            arrayRootObject().emplace_back(relationships);

        if ( !includes.empty() )
            structRootObject().insert("included", includes);

        return JsonAPIAbstractResourceBuilder::build().toString();
    }

    void JsonAPIResourceBuilder::addIncludeResource(std::unique_ptr<Foundation::Hateoas::ResourceBuilderInterface> includedResource)
    {
        includes.emplace_back(includedResource->build());
    }

    void JsonAPIResourceBuilder::addRelatedResource(std::unique_ptr<Foundation::Hateoas::RelatedResourceBuilderInterface> resourceBuilder)
    {
        relationships[resourceBuilder->identifier()] = resourceBuilder->build();
    }


}
