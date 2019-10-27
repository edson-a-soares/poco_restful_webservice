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

#ifndef Foundation_Hateoas_ResourceCollectionInterface_INCLUDED
#define Foundation_Hateoas_ResourceCollectionInterface_INCLUDED

#include <string>
#include <memory>
#include "Poco/DynamicStruct.h"
#include "Foundation/Hateoas/ResourceBuilderInterface.h"

namespace Foundation {
namespace Hateoas {


    /*!
     * It builds a Json resource collection.
     */
    class ResourceCollectionInterface
    {
    public:
        virtual ~ResourceCollectionInterface() = default;
        virtual void hostedAt(const std::string & host) = 0;
        virtual void addResource(std::unique_ptr<ResourceBuilderInterface>, bool partialRepresentation = true) = 0;

        virtual void withMetadata(const std::string & key, const std::string & value) = 0;
        virtual void withMetadata(const std::string & key, const Poco::DynamicStruct &) = 0;
        virtual void withMetadata(const std::string & key, const Poco::Dynamic::Array &) = 0;

        virtual void linkTo(const std::string &, const std::string &) = 0;
        virtual void linkTo(const std::string &, const Poco::DynamicStruct &) = 0;

    };


} }

#endif
