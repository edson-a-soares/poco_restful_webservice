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

#ifndef Web_Service_Domain_Model_Poll_Option_INCLUDED
#define Web_Service_Domain_Model_Poll_Option_INCLUDED

#include "Poco/DateTime.h"
#include "Domain/Shared/Entity.h"

namespace Domain {
namespace Model {
namespace Poll {


    /*!
     * A Question consists of two or more Options.
     * This class represents the Option abstraction.
     *
     * It is identified by a unique identity.
     * It has a date and time of creation and it has
     * its updates registered.
     *
     * An option has a text that the voter can read to make
     * its choice among all available options. The options
     * can be reorganized inside the Question's list as wished.
     */
    class Option final : public Shared::Entity
    {
    public:
        // Default Constructor
        Option();

        /*!
         * @param identity      Option identity.
         * @param createdAt     Date and time of the Option creation.
         * @param lastUpdatedAt Date and time of the last Option update.
         */
        Option(const std::string &, Poco::DateTime, Poco::DateTime);

        /// Assignment Operator returns by value for supporting immutability.
        Option operator=(const Option &);

        /*!
         * It puts the option in a specific position into the Question option's list.
         *
         * One can reorganize the Question option's list the way it want.
         * However, it must guarantee there's no two options pointed to the same
         * position in the list, and if a new option is going to be added into the
         * available options, this new one must be pointed to right next position after
         * the last one already into the list.
         * If one inserts a new option into the list without specify a position, the new
         * option is going to be positioned at the end of the list.
         *
         * @param number The position wanted in the list.
         */
        void positionAt(int);

        /*!
         * It returns a current position of a option in a Question option's list.
         *
         * @return The position number.
         */
        int positionedAt() const;

        /*!
         * It returns the option's text.
         *
         * @return The option's text.
         */
        std::string text() const;

        // It adds a text to the Question's Option.
        void withText(const std::string &);

        Poco::DateTime createdAt() const;
        Poco::DateTime lastUpdatedAt() const;

    private:
        int positionNumber;
        std::string optionText;
        const Poco::DateTime _createdAt;
        const Poco::DateTime _lastUpdatedAt;

        // It validates the most basic Option's class invariants.
        void assertValid();

    };


} } }

#endif
