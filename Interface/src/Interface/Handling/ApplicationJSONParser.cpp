#include "Poco/JSON/Object.h"
#include "Interface/Handling/ApplicationJSONParser.h"

namespace Interface {
namespace Handling {


    ApplicationJSONParser::ApplicationJSONParser()
        : baseUrl("localhost:8080")
    { }

    ApplicationJSONParser::ApplicationJSONParser(const std::string & url)
        : baseUrl(url)
    { }

    std::string ApplicationJSONParser::getUrl(const std::string & path) const
    {
        return "http://" + baseUrl + path;
    }

    std::string ApplicationJSONParser::toJson(const std::string & version) const
    {

        Poco::JSON::Object::Ptr root  = new Poco::JSON::Object();

        Poco::JSON::Object::Ptr links = new Poco::JSON::Object();
        links->set("self", getUrl("/"));

        root->set("links", links);

        Poco::JSON::Object::Ptr meta = new Poco::JSON::Object();
        meta->set("version", version);

        Poco::JSON::Array::Ptr langs  = new Poco::JSON::Array();

        langs->set(0, "en-US");
        langs->set(1, "pt-BR");

        meta->set("lang", langs);
        root->set("meta", meta);

        std::stringstream stream;
        root->stringify(stream);
        return stream.str();

    }


} }
