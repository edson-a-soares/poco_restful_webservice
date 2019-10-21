#ifndef UnitTests_Http_Context_FakeErrorJSONParser_INCLUDED
#define UnitTests_Http_Context_FakeErrorJSONParser_INCLUDED

#include <string>
#include "Poco/JSON/Parser.h"
#include "Foundation/Http/ErrorParserInterface.h"

namespace UnitTests {
namespace Http {
namespace Context {


    /**
     * Poco HTTPResponse does not send response messages with whitespaces.
     * This class exists for doing two specific things:
     *   1. Replace whitespaces to underscore characters. So, the response message might be tested.
     *   2. Remove any text appended to the error description (e.g., Exception Stacktrace).
     */
    class FakeErrorJSONParser : public Foundation::Http::ErrorParserInterface
    {
    public:
        std::string toJson(
            const std::string & host,
            const std::string & code,
            const std::string & path,
            const std::string & type,
            const std::string & description
        ) override;

    };


    std::string FakeErrorJSONParser::toJson(
            const std::string & host,
            const std::string & code,
            const std::string & path,
            const std::string & type,
            const std::string & description
        )
    {
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

        // It removes the Exception Stacktrace if one is appended to the message.
        errorContent->set("description", description.substr(0, description.find('.')+1));

        std::stringstream stream;
        root->stringify(stream);

        auto jsonMessage = stream.str();
        // It replaces all whitespaces to underscore characters so the message can be tested.
        std::replace(jsonMessage.begin(), jsonMessage.end(), ' ', '_');
        return jsonMessage;
    }


} } }

#endif
