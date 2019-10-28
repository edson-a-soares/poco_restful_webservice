#include "Poll/Domain/QuestionNotFoundException.h"

namespace Poll {
namespace Domain {


    QuestionNotFoundException::QuestionNotFoundException()
        : Exception("Question Not Found")
    {}

    QuestionNotFoundException::QuestionNotFoundException(const std::string & questionIdentity)
        : Exception("Question Not Found", "There is any question with id " + questionIdentity)
    {}


} }
