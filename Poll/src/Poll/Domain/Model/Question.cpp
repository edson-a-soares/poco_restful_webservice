#include "Poco/Exception.h"
#include "Poll/Domain/Model/Question.h"

namespace Poll {
namespace Domain {
namespace Model {


    Question::Question()
        : AbstractEntity(),
          questionText(),
          questionLabel(),
          questionDetails(),
          optionsList(),
          _endsAt(),
          _startsAt(),
          _lastUpdatedAt(),
          _createdAt()
    {
        _lastUpdatedAt  = Poco::DateTime();
        _endsAt         = Poco::DateTime(0, 01, 01);
        _startsAt       = Poco::DateTime(0, 01, 01);

        try {
            assertValidDateValues();
        } catch (Poco::InvalidArgumentException &) {
            throw;
        } catch (Poco::Exception &) {
            throw;
        }
    }

    Question::Question(
        const std::string & id,
        Poco::DateTime createdAt,
        Poco::DateTime lastUpdatedAt,
        const std::list<Option> & options,
        Poco::DateTime startsAt,
        Poco::DateTime endsAt
    )
        : AbstractEntity(id),
          questionText(),
          questionLabel(),
          questionDetails(),
          optionsList(),
          _endsAt(endsAt),
          _startsAt(startsAt),
          _lastUpdatedAt(lastUpdatedAt),
          _createdAt(createdAt)
    {
        try {
            /// Sometimes, the default parameter just do not fulfill the invariant
            /// of the class (_lastUpdatedAt >= createdAt).
            /// As a measure to avoid mistakes when default parameter is used, the
            /// default update time is checked and set only after the creation date.
            if ( _lastUpdatedAt.year() == 0 )
                _lastUpdatedAt = Poco::DateTime();

            assertValidDateValues();
            for ( auto & option : options )
                add(option);

        } catch (Poco::InvalidArgumentException &) {
            throw;
        } catch (Poco::Exception &) {
            throw;
        }
    }

    Question Question::operator=(const Question & self)
    {
        /*
         * It tests if this is the same entity using operator!= of the Entity abstraction.
         * Which is the default for checking if two entity objects are the same.
         */
        if ( *this != self ) {
            Question clonedQuestion(self.identity(), self.createdAt(), self.lastUpdatedAt());

            clonedQuestion.setOptions(self.options());

            clonedQuestion.endAt(      self._endsAt);
            clonedQuestion.startAt(    self._startsAt);
            clonedQuestion.withText(   self.questionText);
            clonedQuestion.withLabel(  self.questionLabel);
            clonedQuestion.withDetails(self.questionDetails);

            return clonedQuestion;
        }

        return *this;
    }

    bool Question::equals(const Foundation::Domain::EntityInterface & question) noexcept
    {
        auto other = dynamic_cast<const Question&>(question);

        return _createdAt.timestamp() == other._createdAt.timestamp()
                && optionsList.size() == other.optionsList.size()
                && questionText       == other.questionText;
    }

    bool Question::opened()
    {
        bool isOpened = true;

        auto now = Poco::DateTime();
        // Year zero means just default initialized.
        if ( _endsAt.year()   == 0 ) isOpened = false;
        if ( _startsAt.year() == 0 ) isOpened = false;
        if ( now > _endsAt )         isOpened = false;

        return isOpened;
    }

    void Question::endAt(Poco::DateTime endingAt)
    {
        if ( _startsAt.year() != 0 && endingAt <= _startsAt ) {
            throw Poco::IllegalStateException(
                "Invalid Starting Date",
                "An ending date can not be set without a valid starting date."
            );
        }
        _endsAt = endingAt;
    }

    Poco::DateTime Question::endAt() const
    {
        return _endsAt;
    }

    void Question::startAt(Poco::DateTime dateTime)
    {
        _startsAt = dateTime;
    }

    Poco::DateTime Question::startAt() const
    {
        return _startsAt;
    }

    Poco::DateTime Question::createdAt() const
    {
        return _createdAt;
    }

    Poco::DateTime Question::lastUpdatedAt() const
    {
        return _lastUpdatedAt;
    }

    void Question::add(Option newOption)
    {
        for ( auto const & option : optionsList ) {
            // If it is a new option being added, skip it.
            if ( newOption.positionedAt() == 0 ) continue;

            if ( newOption.positionedAt() == option.positionedAt() ) {
                throw Poco::InvalidArgumentException(
                    "Overriding Option position",
                    "There is already a option at that position."
                );
            }
        }

        auto size = static_cast<int>(optionsList.size());
        if ( newOption.positionedAt() == 0 )
            newOption.positionAt(size + 1);

        optionsList.push_back(newOption);
    }

    std::string Question::details() const
    {
        return questionDetails;
    }

    void Question::setOptions(const std::list<Option> & list)
    {
        try {
            optionsList.clear();
            for ( auto & option : list )
                add(option);

        } catch (Poco::Exception & exception) {
            exception.rethrow();
        }
    }

    void Question::withDetails(const std::string & details)
    {
        if ( details.length() >= DETAILS_SIZE ) {
            throw Poco::InvalidArgumentException(
                "Invalid Question Details Size",
                "A question details text size must be at most 400 characters."
            );
        }
        questionDetails = details;
    }

    std::string Question::text() const
    {
        return questionText;
    }

    void Question::withText(const std::string & text)
    {
        if ( text.length() >= TEXT_SIZE ) {
            throw Poco::InvalidArgumentException(
                "Invalid Question Text Size",
                "A question text size must be at most 200 characters."
            );
        }
        questionText = text;
    }

    std::string Question::label() const
    {
        return questionLabel;
    }

    void Question::withLabel(const std::string & label)
    {
        if ( label.length() > LABEL_SIZE ) {
            throw Poco::InvalidArgumentException("Question label must have at most 50 characters.");
        }
        questionLabel = label;
    }

    std::list<Option> Question::options() const
    {
        return optionsList;
    }

    void Question::assertValidDateValues()
    {
        /*
         * A Question must not be updated before having been created.
         * It may have an updating date equals, it may or may not be when initializing, or ulterior to a creation date.
         */
        if ( !(_lastUpdatedAt >= _createdAt) ) {
            throw Poco::IllegalStateException(
                "Invalid Update Date",
                "Update date must be ulterior or equal to creation date."
            );
        }

        /*
         * A Question can not be started before having been firstly created.
         * Note.: When initialing, a Question sets its starting year to zero, an unset value.
         * Unset date values are ignored here.
         */
        if ( _startsAt.year() != 0 && _startsAt < _createdAt ) {
            throw Poco::IllegalStateException(
                "Invalid Starting Date",
                "Starting date must be ulterior to creation date."
            );
        }

        /*
         * A Question can not be ended before having been firstly started.
         * Therefore, if there is not even a starting date, it is invalid.
         * Note.: When initialing, a Question sets its ending year to zero, an unset value.
         * Unset date values are ignored here.
         */
        if ( _endsAt.year() != 0 && _startsAt.year() == 0 ) {
            throw Poco::IllegalStateException(
                "Invalid Starting Date",
                "A Question can not have been set a ending date without a starting one."
            );
        }

        if ( _endsAt.year() != 0 && _endsAt < _startsAt ) {
            throw Poco::IllegalStateException(
                "Invalid Ending Date",
                "Ending date must be ulterior to starting date."
            );
        }
    }


} } }
