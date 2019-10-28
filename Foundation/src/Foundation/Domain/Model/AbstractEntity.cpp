#include "Poco/UUIDGenerator.h"
#include "Foundation/Domain/Model/AbstractEntity.h"

namespace Foundation {
namespace Domain {


    AbstractEntity::AbstractEntity()
        : _identity(Poco::UUIDGenerator().createRandom().toString())
    {
        if ( Poco::UUID(_identity).isNull() )
            throw Poco::IllegalStateException(_identity + " is not a valid UUID for an Entity.");
    }

    AbstractEntity::AbstractEntity(const std::string & identity)
        : _identity(identity)
    {
        if ( _identity.length() != 36 || Poco::UUID(_identity).isNull() )
            throw Poco::InvalidArgumentException(identity + " is not a valid UUID for an Entity.");
    }

    bool AbstractEntity::operator==(const EntityInterface & other)
    {
        return this == &other && identity() == other.identity();
    }

    bool AbstractEntity::operator!=(const EntityInterface & other)
    {
        return this != &other && identity() != other.identity();
    }

    std::string AbstractEntity::identity() const
    {
        return _identity;
    }


} }
