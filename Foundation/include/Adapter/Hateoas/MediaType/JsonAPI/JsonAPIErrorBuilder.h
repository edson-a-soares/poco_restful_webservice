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

#ifndef Hateoas_MediaType_JsonAPI_JsonAPIErrorBuilder_INCLUDED
#define Hateoas_MediaType_JsonAPI_JsonAPIErrorBuilder_INCLUDED

#include "Poco/DynamicStruct.h"
#include "Foundation/Hateoas/ErrorBuilderInterface.h"

namespace Hateoas {


    class JsonAPIErrorBuilder : public Foundation::Hateoas::ErrorBuilderInterface
    {
    public:
        JsonAPIErrorBuilder();
        ~JsonAPIErrorBuilder() final = default;

        std::string toString() final;

        void withStatusCode(int) final;
        void withType(const std::string &) final;
        void withDetails(const std::string &) final;
        void sourceAt(const std::string & host, const std::string & path) final;

    private:
        std::string host;
        Poco::DynamicStruct commonError;
        Poco::DynamicStruct rootJsonStructure;
        Poco::Dynamic::Array errorsCollection;
        Poco::DynamicStruct sourceErrorPointer;

    };


}

#endif
