#include "Interface/Handling/JSONAPI/JsonAPIAbstractRelatedResourceBuilder.h"

namespace Interface {
namespace Handling {


    JsonAPIAbstractRelatedResourceBuilder::JsonAPIAbstractRelatedResourceBuilder(
        const std::string & identifier,
        const std::string & url
    )
        : _identifier(identifier),
          JsonAPIAbstractResourceBuilder(url)

    { }

    std::string JsonAPIAbstractRelatedResourceBuilder::identifier() const
    {
        return _identifier;
    }


} }
