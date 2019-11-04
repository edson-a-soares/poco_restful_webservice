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


#ifndef UnitTests_Foundation_Domain_Model_FakeDomainModelObject_INCLUDED
#define UnitTests_Foundation_Domain_Model_FakeDomainModelObject_INCLUDED

#include <list>
#include <string>
#include "Poco/DateTime.h"
#include "Foundation/Domain/Model/AbstractEntity.h"

namespace UnitTests {
namespace Foundation {
namespace Context {


    class FakeDomainModelObject final : public ::Foundation::Domain::AbstractEntity
    {
    public:
        FakeDomainModelObject()
            : AbstractEntity(),
              _name()
        {}

        explicit FakeDomainModelObject(const std::string & identity, std::string name = "default")
            : AbstractEntity(identity),
              _name(std::move(name))
        {}

        std::string name()
        {
            return _name;
        }

    protected:
        bool equals(const EntityInterface & object) noexcept override
        {
            auto other = dynamic_cast<const FakeDomainModelObject&>(object);
            return _name == other.name();
        };

    private:
        std::string _name;

    };


} } }

#endif
