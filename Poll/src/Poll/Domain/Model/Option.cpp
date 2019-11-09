#include "Poco/Exception.h"
#include "Poll/Domain/Model/Option.h"

namespace Poll {
namespace Domain {
namespace Model {


    Option::Option()
        : AbstractEntity(),
          positionNumber(0),
          optionText(),
          _createdAt(),
          _lastUpdatedAt()
    {
        try {
            assertValid();
        } catch (Poco::InvalidArgumentException &) {
            throw;
        }
    }

    Option::Option(const std::string & identity, Poco::DateTime createdAt, Poco::DateTime lastUpdatedAt)
        : AbstractEntity(identity),
          positionNumber(0),
          optionText(),
          _createdAt(createdAt),
          _lastUpdatedAt(lastUpdatedAt)
    {
        try {
            assertValid();
        } catch (Poco::InvalidArgumentException &) {
            throw;
        }
    }

    Option Option::operator=(const Option & self)
    {
        if ( *this != self ) {
            Option clonedOption(self.identity(), self._createdAt, self._lastUpdatedAt);

            clonedOption.withText(  self.optionText);
            clonedOption.positionAt(self.positionNumber);

            return clonedOption;
        }

        return *this;
    }

    bool Option::equals(const Foundation::Domain::EntityInterface & option) noexcept
    {
        auto other = dynamic_cast<const Option&>(option);

        return _createdAt.timestamp() == other._createdAt.timestamp()
               && positionNumber      == other.positionNumber
               && optionText          == other.optionText;
    }

    int Option::positionedAt() const
    {
        return positionNumber;
    }

    void Option::positionAt(int number)
    {
        if ( number <= 0 ) {
            throw Poco::InvalidArgumentException(
                "Invalid Option list position",
                "An Option position can not be less than zero."
            );
        }
        positionNumber = number;
    }

    std::string Option::text() const
    {
        return optionText;
    }

    void Option::withText(const std::string & text)
    {
        if ( text.length() < 10 || text.length() > 120 ) {
            throw Poco::InvalidArgumentException(
                "Option text out of acceptable length",
                "An option text length must be bigger than 10 and smaller than 120 characters."
            );
        }
        optionText = text;
    }

    Poco::DateTime Option::createdAt() const
    {
        return _createdAt;
    }

    Poco::DateTime Option::lastUpdatedAt() const
    {
        return _lastUpdatedAt;
    }

    void Option::assertValid()
    {
        if ( _lastUpdatedAt < _createdAt ) {
            throw Poco::InvalidArgumentException("Invalid updating Date");
        }
    }


} } }
