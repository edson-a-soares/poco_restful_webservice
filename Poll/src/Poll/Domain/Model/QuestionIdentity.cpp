#include "Poll/Domain/Model/QuestionIdentity.h"

namespace Poll {
namespace Domain {
namespace Model {


    QuestionIdentity::QuestionIdentity()
        : AbstractIdentity()
    {}

    QuestionIdentity::QuestionIdentity(const std::string & identity)
        : AbstractIdentity(identity)
    {}


} } }
