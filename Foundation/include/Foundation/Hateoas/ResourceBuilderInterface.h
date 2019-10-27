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

#ifndef Foundation_Hateoas_ResourceBuilderInterface_INCLUDED
#define Foundation_Hateoas_ResourceBuilderInterface_INCLUDED

#include "Foundation/Hateoas/ResourceInterface.h"
#include "Foundation/Hateoas/OutputPayloadInterface.h"

namespace Foundation {
namespace Hateoas {


    class ResourceBuilderInterface
        : public ResourceInterface,
          public OutputPayloadInterface
    {
    public:
        virtual ~ResourceBuilderInterface() = default;
        virtual Poco::DynamicStruct & build() = 0;
        virtual void buildAsPartialRepresentation(bool) = 0;

    };


} }

#endif
