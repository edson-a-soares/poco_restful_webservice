#include "Interface/Handling/JSONAPI/JsonAPIAbstractRootResourceBuilder.h"

namespace Interface {
namespace Handling {


    JsonAPIAbstractRootResourceBuilder::JsonAPIAbstractRootResourceBuilder(const std::string & url)
        : JsonAPIAbstractResourceBuilder(url),
          includes(),
          relationships()
    { }

    Poco::DynamicStruct & JsonAPIAbstractRootResourceBuilder::build()
    {
        if ( !relationships.empty() )
            arrayRootObject().emplace_back(relationships);

        if ( !includes.empty() )
            structRootObject().insert("included", includes);

        return JsonAPIAbstractResourceBuilder::build();
    }

    void JsonAPIAbstractRootResourceBuilder::addRelatedResource(IRelatedResourceBuilder * resourceBuilder)
    {
        relationships[resourceBuilder->identifier()] = resourceBuilder->build();
    }

    void JsonAPIAbstractRootResourceBuilder::addIncludeResource(IJsonAPIResourceBuilder * includedResource)
    {
        includes.emplace_back(includedResource->build());
    }


} }
