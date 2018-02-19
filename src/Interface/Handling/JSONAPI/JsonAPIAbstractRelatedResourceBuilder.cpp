#include "Interface/Handling/JSONAPI/JsonAPIAbstractRelatedResourceBuilder.h"

namespace Interface {
namespace Handling {


    JsonAPIAbstractRelatedResourceBuilder::JsonAPIAbstractRelatedResourceBuilder(
        const std::string & identifier,
        const std::string & url
    )
        : JsonAPIAbstractResourceBuilder(url),
          _identifier(identifier)
    { }

    std::string JsonAPIAbstractRelatedResourceBuilder::identifier() const
    {
        return _identifier;
    }


} }
