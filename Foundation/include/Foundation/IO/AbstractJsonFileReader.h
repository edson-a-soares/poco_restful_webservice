/*
 * (C) Copyright 2019 Edson (http://edsonaraujosoares.com) and others.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Contributors:
 *     Edson Araújo Soares
 */

#ifndef Foundation_IO_AbstractJsonFileReader_INCLUDED
#define Foundation_IO_AbstractJsonFileReader_INCLUDED

#include <map>
#include <vector>
#include "Poco/JSON/Object.h"
#include "Foundation/IO/AbstractFileReader.h"
#include "Foundation/IO/JsonFileReaderInterface.h"

namespace Foundation {
namespace IO {


    class AbstractJsonFileReader :
	    public AbstractFileReader,
        public JsonFileReaderInterface
    {
    public:
        AbstractJsonFileReader() = delete;
        AbstractJsonFileReader(const std::string & path, const std::vector<std::string> & propertiesNames);
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
