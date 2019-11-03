#include <typeinfo>
#include "Poco/UUID.h"
#include "Poco/Exception.h"
#include "Foundation/Domain/Model/Identity.h"
#include "Foundation/Domain/Model/AbstractEntity.h"

namespace Foundation {
namespace Domain {


    AbstractEntity::AbstractEntity()
        : _identity(Identity::UNINITIALIZED)
    {}

    AbstractEntity::AbstractEntity(const std::string & identity)
        : _identity(identity)
    {
        if ( _identity.length() != Identity::SIZE || Poco::UUID(_identity).isNull() )
            throw Poco::InvalidArgumentException(identity + " is not a valid identity for an entity.");
    }

    bool AbstractEntity::operator==(const EntityInterface & other) noexcept
    {
        return typeid(*this) == typeid(other)
                && this == &other
                && equals(other)
                && _identity == other.identity();
    }

    bool AbstractEntity::operator!=(const EntityInterface & other) noexcept
    {
        return typeid(*this) != typeid(other)
                || this != &other
                || !equals(other)
                || _identity != other.identity();
    }

    std::string AbstractEntity::identity() const
    {
        return _identity;
    }


} }
