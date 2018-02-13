#include "Interface/Handling/JsonAPIResourceBuilder.h"

namespace Interface {
namespace Handling {


    JsonAPIResourceBuilder::JsonAPIResourceBuilder()
        : JsonAPIAbstractRootResourceBuilder("")
    { }

    JsonAPIResourceBuilder::JsonAPIResourceBuilder(const std::string & url)
        : JsonAPIAbstractRootResourceBuilder(url)
    { }

    JsonAPIResourceBuilder::~JsonAPIResourceBuilder()
    { }


} }
