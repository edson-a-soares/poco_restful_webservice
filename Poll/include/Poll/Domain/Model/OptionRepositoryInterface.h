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

#ifndef Poll_Domain_Model_OptionRepositoryInterface_INCLUDED
#define Poll_Domain_Model_OptionRepositoryInterface_INCLUDED

#include <list>
#include <string>
#include "Poll/Domain/Model/Option.h"
#include "Poll/Domain/Model/OptionIdentity.h"
#include "Poll/Domain/Model/QuestionIdentity.h"

namespace Poll {
namespace Domain {
namespace Model {


    class OptionRepositoryInterface
    {
    public:
        virtual ~OptionRepositoryInterface() = default;

        /*!
         * It either stores or updates a given option.
         *
         * @param options The option to handle.
         */
        virtual void add(const QuestionIdentity &, const Option &) = 0;

        /*!
         * It either stores or updates a given list of options.
         *
         * The questions which exist will be updated. The ones that doesn't will be inserted.
         *
         * @param options The list of options to handle.
         */
        virtual void insert(const QuestionIdentity &, const std::list<Option> &) = 0;

        /*!
         * It removes an option and their related data.
         *
         * @param option The Option to be removed.
         */
        virtual void remove(const Option &) = 0;

        /*!
         * It destroys a list of options and all their related data.
         *
         * @param options The option's list to be erased.
         */
        virtual void erase(const std::list<Option> &) = 0;

        /*!
         * It finds an option using its identity.
         *
         * @param identity The Option's identity.
         * @return The Option, if found. If not, it throws an OptionNotFoundException.
         */
        virtual Option withIdentity(const OptionIdentity &) = 0;

        /*!
         * It finds all options of a given question using its identity.
         *
         * @param identity The question's identity.
         * @return The list of found Options list.
         */
        virtual std::list<Option> allWith(const QuestionIdentity & identity) = 0;

    };


} } }

#endif
