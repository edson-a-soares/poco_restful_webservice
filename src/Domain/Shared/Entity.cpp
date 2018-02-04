#include "Domain/Shared/Entity.h"
#include "Poco/UUIDGenerator.h"

namespace Domain {
namespace Shared {


    Entity::Entity()
        : _identity(Poco::UUIDGenerator().createOne().toString())
    {

        if ( Poco::UUID(_identity).isNull() ) {
            throw Poco::IllegalStateException(
                _identity + " is not a valid UUID for an Entity."
            );
        }

    }

    Entity::Entity(const std::string & identity)
        : _identity(identity)
    {

        if ( _identity.length() != 36 || Poco::UUID(_identity).isNull() ) {
            throw Poco::InvalidArgumentException(
                identity + " is not a valid UUID for an Entity."
            );
        }

    }

    Entity::~Entity()
    { }

    bool Entity::operator==(const IEntity & other)
    {
        return this == &other && identity() == other.identity();
    }

    bool Entity::operator!=(const IEntity & other)
    {
        return this != &other && identity() != other.identity();
    }

    std::string Entity::identity() const
    {
        return _identity;
    }


} }
