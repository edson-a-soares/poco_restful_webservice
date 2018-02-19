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

#ifndef Web_Service_Interface_Handling_JSONAPI_Abstract_Resource_Builder_INCLUDED
#define Web_Service_Interface_Handling_JSONAPI_Abstract_Resource_Builder_INCLUDED

#include "Interface/Handling/JSONAPI/IJsonAPIResourceBuilder.h"

namespace Interface {
namespace Handling {


    /*!
     * It just make available Json API Resource Builder functions implementations
     * to other classes.
     *
     * @see IJsonAPIResourceBuilder
     */
    class JsonAPIAbstractResourceBuilder : public IJsonAPIResourceBuilder
    {
    public:
        // Default Destructor
        ~JsonAPIAbstractResourceBuilder() override = default;

        Poco::DynamicStruct & build() override;

        void hostedAt(const std::string &) override;
        void withType(const std::string &) override;
        void withIdentity(const std::string &) override;

        void linkTo(const std::string &, const std::string &) override;
        void linkTo(const std::string &, const Poco::DynamicStruct &) override;

        void addAttribute(const std::string &, const std::string &) override;
        void addAttribute(const std::string &, const Poco::DynamicAny &) override;

        void withMetadata(const std::string &, const std::string &) override;
        void withMetadata(const std::string &, const Poco::DynamicStruct &) override;
        void withMetadata(const std::string &, const Poco::Dynamic::Array &) override;

    protected:
        explicit JsonAPIAbstractResourceBuilder(const std::string &);

        Poco::DynamicStruct & structRootObject();
        Poco::Dynamic::Array & arrayRootObject();

    private:
        Poco::DynamicStruct links;
        std::string resourceRootURL;
        Poco::DynamicStruct metadata;
        Poco::DynamicStruct attributes;
        Poco::DynamicStruct structRoot;
        Poco::DynamicStruct resourceBasic;
        Poco::Dynamic::Array dataArrayRoot;

    };


} }

#endif
