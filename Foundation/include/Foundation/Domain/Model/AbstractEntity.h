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

#ifndef Foundation_Domain_Model_AbstractEntity_INCLUDED
#define Foundation_Domain_Model_AbstractEntity_INCLUDED

#include <string>
#include "Foundation/Domain/Model/EntityInterface.h"

namespace Foundation {
namespace Domain {


    class AbstractEntity : public EntityInterface
    {
    public:
        virtual ~AbstractEntity() = default;
        std::string identity() const final;
        bool operator==(const EntityInterface &) noexcept final;
        bool operator!=(const EntityInterface &) noexcept final;

    protected:
        AbstractEntity();
        explicit AbstractEntity(const std::string & identity);
        virtual bool equals(const EntityInterface &) noexcept = 0;

    private:
        const std::string _identity;

    };


} }

#endif
