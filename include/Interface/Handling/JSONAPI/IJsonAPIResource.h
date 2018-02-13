/*
 * (C) Copyright 2018 Edson (http://edsonaraujosoares.com) and others.
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

#ifndef Web_Service_Interface_Handling_JSONAPI_IResource_INCLUDED
#define Web_Service_Interface_Handling_JSONAPI_IResource_INCLUDED

#include <string>
#include "Poco/DynamicStruct.h"

namespace Interface {
namespace Handling {


    /*!
     * It builds a Json API main resource.
     *
     * @see http://jsonapi.org
     */
    class IJsonAPIResource
    {
    public:
        virtual void hostedAt(const std::string &) = 0;
        virtual void withType(const std::string &) = 0;
        virtual void withIdentity(const std::string &) = 0;

        virtual void linkTo(const std::string &, const std::string &) = 0;
        virtual void linkTo(const std::string &, const Poco::DynamicStruct &) = 0;

        virtual void addAttribute(const std::string &, const std::string &) = 0;
        virtual void addAttribute(const std::string &, const Poco::DynamicAny &) = 0;

        virtual void withMetadata(const std::string &, const std::string &) = 0;
        virtual void withMetadata(const std::string &, const Poco::DynamicStruct &) = 0;
        virtual void withMetadata(const std::string &, const Poco::Dynamic::Array &) = 0;

    };


} }

#endif
