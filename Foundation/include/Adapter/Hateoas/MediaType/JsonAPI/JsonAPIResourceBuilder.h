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

#ifndef Hateoas_MediaType_JsonAPI_JsonAPIResourceBuilder_INCLUDED
#define Hateoas_MediaType_JsonAPI_JsonAPIResourceBuilder_INCLUDED

#include <memory>
#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIAbstractResourceBuilder.h"
#include "Adapter/Hateoas/MediaType/JsonAPI/JsonAPIAbstractRelatedResourceBuilder.h"

namespace Hateoas {


    class JsonAPIResourceBuilder : public JsonAPIAbstractResourceBuilder
    {
    public:
        JsonAPIResourceBuilder();
        ~JsonAPIResourceBuilder() override = default;

        void addIncludeResource(std::unique_ptr<Foundation::Hateoas::ResourceBuilderInterface>);
        void addRelatedResource(std::unique_ptr<Foundation::Hateoas::RelatedResourceBuilderInterface>);

        std::string toString() final;

    private:
        Poco::Dynamic::Array includes;
        Poco::DynamicStruct relationships;

    };


}

#endif
