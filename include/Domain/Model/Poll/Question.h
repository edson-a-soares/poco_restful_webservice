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


#ifndef Web_Service_Domain_Model_Poll_Question_INCLUDED
#define Web_Service_Domain_Model_Poll_Question_INCLUDED

#include <list>
#include "Poco/DateTime.h"
#include "Domain/Shared/Entity.h"
#include "Domain/Model/Poll/Option.h"

namespace Domain {
namespace Model {
namespace Poll {


    /*!
     * Question is the central class of the Poll's Context.
     * It is its aggregate root. Therefore, all operations
     * are going to be performed through it.
     *
     * A Question is a sentence worked or expressed to elicit
     * information. It is identified by a unique identity and
     * always is also composed by a set of options. These
     * options are which voters will choose during the polling
     * process.
     *
     * The question's lifecycle begins with a question creation.
     * A date and time is set to finish the pooling process.
     * When this moment is arrived, the question's lifecycle ends.
     */
    class Question final : public Shared::Entity
    {
    public:
        /// User-defined Default constructor
        Question();

        /*!
         * @param identity      The unique identity of the Question.
         * @param options       The set of Options to the Question.
         * @param createdAt     Question creation date and time.
         * @param lastUpdatedAt Question update date and time.
         * @param startsAt      Date and time a Question will be available to be voted.
         * @param endsAt        Date and time to the end of the polling process.
         */
        explicit Question(
            const std::string & identity,
            const std::list<Option> & options   = {},
            Poco::DateTime createdAt            = Poco::DateTime(),
            Poco::DateTime lastUpdatedAt        = Poco::DateTime(0, 01, 01),
            Poco::DateTime startsAt             = Poco::DateTime(0, 01, 01),
            Poco::DateTime endsAt               = Poco::DateTime(0, 01, 01)
        );

        // Assignment Operator returns by value for supporting immutability.
        Question operator=(const Question &);

        // Check if the Question still is available to be voted.
        bool isOpened();

        Poco::DateTime endAt() const;
        void endAt(Poco::DateTime);

        Poco::DateTime startAt() const;
        void startAt(Poco::DateTime);

        Poco::DateTime createdAt() const;
        Poco::DateTime lastUpdatedAt() const;

        void add(Option);
        void setOptions(const std::list<Option> &);
        std::list<Option> options() const;

        std::string text() const;
        void withText(const std::string &);

        std::string label() const;
        void withLabel(const std::string &);

        std::string details() const;
        void withDetails(const std::string &);

    private:
        static constexpr int TEXT_SIZE    = 200;
        static constexpr int LABEL_SIZE   = 50;
        static constexpr int DETAILS_SIZE = 400;

        std::string questionText;
        std::string questionLabel;
        std::string questionDetails;
        std::list<Option> optionsList;

        Poco::DateTime _endsAt;
        Poco::DateTime _startsAt;
        Poco::DateTime _lastUpdatedAt;
        const Poco::DateTime _createdAt;

        /// It validates most basic Question class invariants.
        void assertValidDateValues();

    };


} } }

#endif
