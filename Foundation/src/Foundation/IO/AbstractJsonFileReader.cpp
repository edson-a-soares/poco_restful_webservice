#include "Poco/JSON/Parser.h"
#include "Foundation/IO/AbstractJsonFileReader.h"

namespace Foundation {
namespace IO {


    AbstractJsonFileReader::AbstractJsonFileReader(const std::string & path, const std::vector<std::string> & propertiesNames)
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

    std::string AbstractJsonFileReader::fetch(const std::string & name)
    {
        poco_assert_msg(!name.empty(), "Property identifier must not be empty.");
        poco_assert_msg(properties.count(name) > 0, "Property identifier error. Property does not exist.");

    	return properties[name];
    }

    std::string AbstractJsonFileReader::readArray(Poco::JSON::Object::Ptr & jsonObject, const std::string & propertyName)
    {
        std::string nodeList;
        try {

            if ( !jsonObject->has(propertyName) )
                throw Poco::PropertyNotSupportedException(
                    "Not-Existent JSON property",
                    "Property " + propertyName + " does not exist in the file specified."
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

    std::string AbstractJsonFileReader::readProperty(Poco::JSON::Object::Ptr & jsonObject, const std::string & propertyName)
    {
        std::string property;
        try {

            if ( !jsonObject->has(propertyName) )
                throw Poco::PropertyNotSupportedException(
                    "Not-Existent JSON property",
                    "Property " + propertyName + " does not exist in the file specified."
                );

            property = jsonObject->getValue<std::string>(propertyName);
            if ( property.empty() )
                throw Poco::NullValueException(
                    "Empty JSON property",
                    "Property " + propertyName + " is empty."
                );

        } catch (Poco::Exception &) {
            throw;
        }

        return property;
    }

	void AbstractJsonFileReader::handleFileContent(const std::string & jsonData)
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
