#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIResourceCollectionBuilder.h"

namespace Hateoas {


    JsonAPIResourceCollectionBuilder::JsonAPIResourceCollectionBuilder()
        : links(),
          resourceRootURL(),
          metadata(),
          structRoot(),
          resourceBasic(),
          dataArrayRoot()
    {}

    std::string JsonAPIResourceCollectionBuilder::toString()
    {
        if ( !links.empty() )
            resourceBasic.insert("links", links);

        if ( !resourceBasic.empty() )
            dataArrayRoot.emplace_back(resourceBasic);

        if ( !metadata.empty() )
            structRoot.insert("meta", metadata);

        structRoot.insert("data", dataArrayRoot);
        return structRoot.toString();
    }

    void JsonAPIResourceCollectionBuilder::hostedAt(const std::string & host)
    {
        resourceRootURL = host;
    }

    void JsonAPIResourceCollectionBuilder::linkTo(const std::string & key, const std::string & value)
    {
        links[key] = "http://" + resourceRootURL + value;
    }

    void JsonAPIResourceCollectionBuilder::linkTo(const std::string & key, const Poco::DynamicStruct & buildingStruct)
    {
        links[key] = buildingStruct;
    }

    void JsonAPIResourceCollectionBuilder::withMetadata(const std::string & key, const std::string & value)
    {
        metadata.insert(key, value);
    }

    void JsonAPIResourceCollectionBuilder::withMetadata(const std::string & key, const Poco::DynamicStruct & value)
    {
        metadata.insert(key, value);
    }

    void JsonAPIResourceCollectionBuilder::withMetadata(const std::string & key, const Poco::Dynamic::Array & value)
    {
        metadata.insert(key, value);
    }

    void JsonAPIResourceCollectionBuilder::addResource(std::unique_ptr<Foundation::Hateoas::ResourceBuilderInterface> resourceBuilder, bool partialRepresentation)
    {
        resourceBuilder->buildAsPartialRepresentation(partialRepresentation);
        dataArrayRoot.emplace_back(resourceBuilder->build());
    }


}
