#include <typeinfo>
#include "Poco/UUIDGenerator.h"
#include "Foundation/Domain/Model/Identity.h"
#include "Foundation/Domain/Model/AbstractIdentity.h"

namespace Foundation {
namespace Domain {


    AbstractIdentity::AbstractIdentity()
        : _identity(Poco::UUIDGenerator().createRandom().toString())
    {
        if ( Poco::UUID(_identity).isNull() )
            throw Poco::IllegalStateException(_identity + " is not a valid identity for an entity.");
    }

    AbstractIdentity::AbstractIdentity(const std::string & identity)
        : _identity(identity)
    {
        if ( _identity.length() != Identity::SIZE || Poco::UUID(_identity).isNull() )
            throw Poco::InvalidArgumentException(identity + " is not a valid identity for an entity.");
    }

    std::string AbstractIdentity::toString() const
    {
        return _identity;
    }

    bool AbstractIdentity::operator==(const IdentityInterface & other) noexcept
    {
        return typeid(*this) == typeid(other)
                && this == &other
                && _identity == other.toString();
    }

    bool AbstractIdentity::operator!=(const IdentityInterface & other) noexcept
    {
        return typeid(*this) != typeid(other)
                || this != &other
                || _identity != other.toString();
    }


} }
