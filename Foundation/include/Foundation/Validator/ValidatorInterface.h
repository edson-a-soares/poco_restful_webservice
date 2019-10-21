#ifndef Foundation_Validator_ValidatorInterface_INCLUDED
#define Foundation_Validator_ValidatorInterface_INCLUDED

#include <string>

namespace Foundation {
namespace Validator {


    class ValidatorInterface
    {
    public:
        virtual ~ValidatorInterface() = default;
        virtual bool valid() = 0;
        virtual std::string message() const = 0;

    };


} }

#endif
