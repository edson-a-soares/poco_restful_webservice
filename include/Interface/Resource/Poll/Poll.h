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

#ifndef Web_Service_Interface_Resource_Poll_Poll_INCLUDED
#define Web_Service_Interface_Resource_Poll_Poll_INCLUDED

#include "Application/IPollService.h"
#include "Interface/Resource/AbstractResource.h"
#include "Interface/Handling/Assembler/QuestionAssembler.h"

namespace Interface {
namespace Resource {
namespace Poll {


    class Poll : public AbstractResource
    {
    public:
        // Default Constructor
        Poll();

        // Default Destructor
        ~Poll() override;

        void setApplicationService(Application::IPollService *);
        void setEntityAssembler(Interface::Handling::QuestionAssembler &);

    protected:

        /**
         * @see AbstractResource::handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

        /**
         * @see AbstractResource::handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

        /**
         * @see AbstractResource::handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

        /**
         * @see AbstractResource::handle_delete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handle_delete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

        /**
         * @see AbstractResource::handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &)
         */
        void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    private:
        Application::IPollService * pollApplicationService;
        Interface::Handling::QuestionAssembler entityAssembler;

    };


} } }

#endif
