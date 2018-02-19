#include "Poco/JSON/Object.h"
#include "Interface/Handling/JSONAPI/JsonAPIErrorBuilder.h"

namespace Interface {
namespace Handling {


    JsonAPIErrorBuilder::JsonAPIErrorBuilder(const std::string & url)
        : host(url),
          commonError(),
          rootJsonStructure(),
          errorsCollection(),
          sourceErrorPointer()

    { }

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

    void JsonAPIErrorBuilder::sourceAt(const std::string & pointer)
    {
        sourceErrorPointer.insert("pointer", host + pointer);
    }

    Poco::DynamicStruct & JsonAPIErrorBuilder::build()
    {
        commonError.insert("source", sourceErrorPointer);
        errorsCollection.push_back(commonError);

        rootJsonStructure.insert("error", errorsCollection);
        return rootJsonStructure;
    }


} }
