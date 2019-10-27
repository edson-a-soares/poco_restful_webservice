#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIErrorBuilder.h"

namespace Hateoas {


    JsonAPIErrorBuilder::JsonAPIErrorBuilder()
        : host(),
          commonError(),
          rootJsonStructure(),
          errorsCollection(),
          sourceErrorPointer()
    {}

    void JsonAPIErrorBuilder::withStatusCode(int code)
    {
        commonError.insert("status", code);
    }

    void JsonAPIErrorBuilder::withType(const std::string & type)
    {
        commonError.insert("type", type);
    }

    void JsonAPIErrorBuilder::withDetails(const std::string & text)
    {
        commonError.insert("details", text);
    }

    void JsonAPIErrorBuilder::sourceAt(const std::string & host, const std::string & path)
    {
        sourceErrorPointer.insert("pointer", host + path);
    }

    std::string JsonAPIErrorBuilder::toString()
    {
        commonError.insert("source", sourceErrorPointer);
        errorsCollection.push_back(commonError);

        rootJsonStructure.insert("error", errorsCollection);
        return rootJsonStructure.toString();
    }


}
