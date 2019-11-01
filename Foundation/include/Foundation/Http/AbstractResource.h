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

#ifndef Foundation_Http_AbstractResource_INCLUDED
#define Foundation_Http_AbstractResource_INCLUDED

#include <memory>
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Foundation/Http/ErrorParserInterface.h"
#include "Foundation/Http/CORSConfigurationInterface.h"

namespace Foundation {
namespace Http {


    class AbstractResource : public Poco::Net::HTTPRequestHandler
    {
    public:
        ~AbstractResource() override = default;
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    protected:
        static std::unique_ptr<Foundation::Http::CORSConfigurationInterface> corsHeaders();
        virtual std::unique_ptr<ErrorParserInterface> errorParser();

        virtual void handle_get(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_put(    Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_post(   Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_patch(  Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_delete( Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);
        virtual void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

    private:
        static void corsHeaders(Poco::Net::HTTPServerResponse &);

    };


} }

#endif
