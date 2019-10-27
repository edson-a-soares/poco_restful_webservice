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

#ifndef Foundation_Hateoas_MediaTypeAbstractFactoryInterface_INCLUDED
#define Foundation_Hateoas_MediaTypeAbstractFactoryInterface_INCLUDED

#include <memory>
#include "Foundation/Hateoas/ErrorBuilderInterface.h"
#include "Foundation/Hateoas/ResourceBuilderInterface.h"
#include "Foundation/Hateoas/ResourceCollectionBuilderInterface.h"

namespace Foundation {
namespace Hateoas {


    class MediaTypeAbstractFactoryInterface
    {
    public:
        virtual ~MediaTypeAbstractFactoryInterface() = default;
        virtual std::unique_ptr<ErrorBuilderInterface> error() = 0;
        virtual std::unique_ptr<ResourceBuilderInterface> resource() = 0;
        virtual std::unique_ptr<ResourceCollectionBuilderInterface> collection() = 0;

    };


} }

#endif
