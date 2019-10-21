#include "Poco/JSON/Parser.h"
#include "Foundation/IO/AbstractJSONFileReader.h"

namespace Foundation {
namespace IO {


    AbstractJSONFileReader::AbstractJSONFileReader(const std::string & path, const std::vector<std::string> & propertiesNames)
        : AbstractFileReader(path),
          properties(),
          jsonFilePropertiesNames(propertiesNames)
    {
	    try {
            handleFileContent(read());
	    } catch (Poco::Exception &) {
	    	throw;
	    }
    }

    std::string AbstractJSONFileReader::fetch(const std::string & name)
    {
        poco_assert_msg(!name.empty(), "Property identifier must not be empty.");
        poco_assert_msg(properties.count(name) > 0, "Property identifier error. Property does not exist.");

    	return properties[name];
    }

    std::string AbstractJSONFileReader::readArray(Poco::JSON::Object::Ptr & jsonObject, const std::string & propertyName)
    {
        std::string nodeList;
        try {

            if ( !jsonObject->has(propertyName) )
                throw Poco::PropertyNotSupportedException(
                    "Not-Existent JSON File property",
                    "Property " + propertyName + " does not exist in the file specified.",
                    00010
                );

            auto list = jsonObject->getArray(propertyName);
            std::size_t originalListSize = list->size() - 1;

            for ( unsigned int counter = 0; counter < originalListSize; counter++ )
                nodeList += list->get(counter).toString() + ", ";

            nodeList += list->get(static_cast<int>(originalListSize)).toString();

        } catch (Poco::Exception &) {
            throw;
        }

        return nodeList;
    }

    std::string AbstractJSONFileReader::readProperty(Poco::JSON::Object::Ptr & jsonObject, const std::string & propertyName)
    {
        std::string property;
        try {

            if ( !jsonObject->has(propertyName) )
                throw Poco::PropertyNotSupportedException(
                        "Not-Existent JSON File property",
                        "Property " + propertyName + " does not exist in the file specified.",
                        00010
                );

            property = jsonObject->getValue<std::string>(propertyName);
            if ( property.empty() )
                throw Poco::NullValueException(
                        "Empty JSON File Configuration property",
                        "Property " + propertyName + " is empty.",
                        00010
                );

        } catch (Poco::Exception &) {
            throw;
        }

        return property;
    }

	void AbstractJSONFileReader::handleFileContent(const std::string & jsonData)
	{
		Poco::JSON::Parser jsonParser;
		try {
            Poco::Dynamic::Var parserResult    = jsonParser.parse(jsonData);
            Poco::JSON::Object::Ptr jsonObject = parserResult.extract<Poco::JSON::Object::Ptr>();

		    for (const auto & property : jsonFilePropertiesNames) {
		        if (jsonObject->isArray(property)) {
                    properties[property] = readArray(jsonObject, property);
                    continue;
                }

                properties[property] = readProperty(jsonObject, property);
		    }

		} catch (Poco::Exception &) {
			throw;
		}
	}


} }
