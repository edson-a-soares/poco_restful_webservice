#ifndef Foundation_IO_AbstractJSONFileReader_INCLUDED
#define Foundation_IO_AbstractJSONFileReader_INCLUDED

#include <map>
#include <vector>
#include "Poco/JSON/Object.h"
#include "Foundation/IO/AbstractFileReader.h"
#include "Foundation/IO/JSONFileReaderInterface.h"

namespace Foundation {
namespace IO {


    class AbstractJSONFileReader :
	    public AbstractFileReader,
        public JSONFileReaderInterface
    {
    public:
        AbstractJSONFileReader() = delete;
        AbstractJSONFileReader(const std::string & path, const std::vector<std::string> & propertiesNames);
	    std::string fetch(const std::string & name) final;

    private:
    	void handleFileContent(const std::string & jsonData);
        static std::string readArray(Poco::JSON::Object::Ptr & jsonObject, const std::string & propertyName);
    	static std::string readProperty(Poco::JSON::Object::Ptr & jsonObject, const std::string & propertyName);

    	std::map<std::string, std::string> properties;
        std::vector<std::string> jsonFilePropertiesNames;

    };


} }

#endif
