#include "Poll/Domain/Model/OptionIdentity.h"

namespace Poll {
namespace Domain {
namespace Model {


    OptionIdentity::OptionIdentity()
        : AbstractIdentity()
    {}

    OptionIdentity::OptionIdentity(const std::string & identity)
        : AbstractIdentity(identity)
    {}


} } }
