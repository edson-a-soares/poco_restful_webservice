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

#ifndef Foundation_Domain_Model_AbstractIdentity_INCLUDED
#define Foundation_Domain_Model_AbstractIdentity_INCLUDED

#include <string>
#include "Foundation/Domain/Model/IdentityInterface.h"

namespace Foundation {
namespace Domain {


    class AbstractIdentity : public IdentityInterface
    {
    public:
        virtual ~AbstractIdentity() = default;
        std::string toString() const final;
        bool operator==(const IdentityInterface &) noexcept final;
        bool operator!=(const IdentityInterface &) noexcept final;

    protected:
        AbstractIdentity();
        explicit AbstractIdentity(const std::string & identity);

    private:
        const std::string _identity;

    };


} }

#endif
