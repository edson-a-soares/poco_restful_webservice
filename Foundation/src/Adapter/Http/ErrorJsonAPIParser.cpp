#include "Poco/JSON/Object.h"
#include "Adapter/Http/ErrorJsonAPIParser.h"

namespace Http {


    std::string ErrorJsonAPIParser::toJson(
        const std::string & host,
        const std::string & code,
        const std::string & path,
        const std::string & type,
        const std::string & description
    ) {
        // { ... }
        Poco::JSON::Object::Ptr root = new Poco::JSON::Object();

		// "error" : []
		Poco::JSON::Array::Ptr error = new Poco::JSON::Array();
		root->set("error", error);

		// "error" : [{ ... }]
		Poco::JSON::Object::Ptr errorContent = new Poco::JSON::Object();

		errorContent->set("code", code);
		error->set(0, errorContent);

		// "source" : { ... }
		Poco::JSON::Object::Ptr source = new Poco::JSON::Object();
		source->set("pointer", "http://" + host + path);

		errorContent->set("source",      source);
		errorContent->set("type",        type);
		errorContent->set("description", description);

		std::stringstream stream;
		root->stringify(stream);
		return stream.str();
    }


}
