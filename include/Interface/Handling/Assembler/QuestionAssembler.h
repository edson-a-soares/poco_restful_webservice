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

#ifndef Web_Service_Interface_Handling_Assembler_Question_Assembler_INCLUDED
#define Web_Service_Interface_Handling_Assembler_Question_Assembler_INCLUDED

#include "Poco/JSON/Object.h"
#include "Application/IPollService.h"
#include "Domain/Model/Poll/Question.h"
#include "Interface/Handling/JsonAPIResourceBuilder.h"

namespace Interface {
namespace Handling {


    class QuestionAssembler
    {
    public:
        QuestionAssembler();

        void setURI(const std::string &);
        void setHost(const std::string &);
        std::string toJson(const std::list<Application::PollResult> &);
        std::string toJson(const Domain::Model::Poll::Question &);

        Domain::Model::Poll::Question assembleEntity(const Poco::JSON::Object::Ptr &);
        std::list<Domain::Model::Poll::Option> assembleOptionsList(const Poco::JSON::Object::Ptr &);

    private:
        std::string URI;
        std::string host;

    };


} }

#endif
