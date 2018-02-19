#include "Interface/Handling/JSONAPI/JsonAPIResourceCollectionBuilder.h"

namespace Interface {
namespace Handling {


    JsonAPIResourceCollectionBuilder::JsonAPIResourceCollectionBuilder()
        : links(),
          resourceRootURL(),
          metadata(),
          structRoot(),
          resourceBasic(),
          dataArrayRoot()
    { }

    Poco::DynamicStruct & JsonAPIResourceCollectionBuilder::build()
    {

        if ( !links.empty() )
            resourceBasic.insert("links", links);

        if ( !resourceBasic.empty() )
            dataArrayRoot.emplace_back(resourceBasic);

        if ( !metadata.empty() )
            structRoot.insert("meta", metadata);

        structRoot.insert("data", dataArrayRoot);
        return structRoot;

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

    void JsonAPIResourceCollectionBuilder::withMetadata(const std::string & value)
    {
        metadata.insert("meta", value);
    }

    void JsonAPIResourceCollectionBuilder::withMetadata(const Poco::DynamicStruct & value)
    {
        metadata.insert("meta", value);
    }

    void JsonAPIResourceCollectionBuilder::withMetadata(const Poco::Dynamic::Array & value)
    {
        metadata.insert("meta", value);
    }

    void JsonAPIResourceCollectionBuilder::addResource(IJsonAPIResourceBuilder * resourceBuilder)
    {
        dataArrayRoot.emplace_back(resourceBuilder->build());
    }


} }
