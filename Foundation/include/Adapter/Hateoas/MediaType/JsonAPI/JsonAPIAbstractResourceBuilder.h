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

#ifndef Hateoas_MediaType_JsonAPI_JsonAPIAbstractResourceBuilder_INCLUDED
#define Hateoas_MediaType_JsonAPI_JsonAPIAbstractResourceBuilder_INCLUDED

#include "Foundation/Hateoas/ResourceBuilderInterface.h"

namespace Hateoas {


    /*!
     * It just make available Json API Resource Builder functions implementations to other classes.
     *
     * @see Foundation::Hateoas::ResourceBuilderInterface
     */
    class JsonAPIAbstractResourceBuilder : public Foundation::Hateoas::ResourceBuilderInterface
    {
    public:
        JsonAPIAbstractResourceBuilder();
        ~JsonAPIAbstractResourceBuilder() override = default;

        /*
         * @see Foundation::Hateoas::OutputPayloadInterface
         */
        std::string toString() override = 0;

        Poco::DynamicStruct & build() final;
        void buildAsPartialRepresentation(bool) final;

        void hostedAt(const std::string &) override;
        void withType(const std::string &) override;
        void withIdentity(const std::string &) override;

        void linkTo(const std::string &, const std::string &) override;
        void linkTo(const std::string &, const Poco::DynamicStruct &) override;

        void addAttribute(const std::string &, const std::string &) override;

        void withMetadata(const std::string &, const std::string &) override;
        void withMetadata(const std::string &, const Poco::Dynamic::Array &) override;

    protected:
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
        bool _buildAsBasicRepresentationOnly;

    };


}

#endif
