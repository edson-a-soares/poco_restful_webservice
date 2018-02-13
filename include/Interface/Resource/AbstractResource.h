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

#ifndef Web_Service_Interface_Resource_Abstract_Resource_INCLUDED
#define Web_Service_Interface_Resource_Abstract_Resource_INCLUDED

#include "Poco/URI.h"
#include "Poco/JSON/Object.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Interface/Resource/Exception.h"
#include "Interface/Handling/JsonAPIResourceBuilder.h"

namespace Interface {
namespace Resource {


    class AbstractResource : public Poco::Net::HTTPRequestHandler
    {
    public:
        // Default User-defined Constructor
        AbstractResource();

        // Default Destructor
        ~AbstractResource() override;

        /*!
         * @see Poco::Net::HTTPRequestHandler
         */
        void handleRequest(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &) override;

    protected:

        /// It handles to Http verb GET.
        virtual void handle_get(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        /// It handles to Http verb PUT.
        virtual void handle_put(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        /// It handles to Http verb POST.
        virtual void handle_post(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        /// It handles to Http verb DELETE.
        virtual void handle_delete(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        /// It handles to Http VERB OPTIONS.
        virtual void handle_options(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        /// It validates required information into the Http headers.
        virtual void handleHttpHeaders(Poco::Net::HTTPServerRequest &, Poco::Net::HTTPServerResponse &);

        /**
         * @param payload The string containing the Json data.
         * @return Only part of the payload with attributes in Poco Json Object format.
         */
        Poco::JSON::Object::Ptr getJsonAttributesSectionObject(const std::string &);

        /*!
         * It validates a set of parameters have been set in a Json payload.
         *
         * @param jsonObject        Poco Json Object that contains payload data.
         * @param attributesNames   Attributes list to be validated.
         */
        void assertPayloadAttributes(const Poco::JSON::Object::Ptr &, const std::list<std::string> &);

        /*!
         * It sets all the HTTP Response information based on the HTTP Code.
         *
         * @param statusCode    The HTTP Status Code.
         * @param response      Response to be handled.
         */
        void handleHttpStatusCode(int statusCode, Poco::Net::HTTPServerResponse &);

        /*!
         * @param fragment Part that it wishes to add to a URL.
         * @return A complete URL with a fragment added to its end.
         */
        std::string getUrl(const std::string & fragment);

        /*!
         * It converts an exception to Json API format.
         *
         * @param exception The exception thrown.
         * @return The exception Json API formatted.
         */
        std::string toJson(const Exception &);

        /*!
         * @param name The parameter name.
         * @return The parameter value.
         */
        std::string getQueryParameter(const std::string &);

    private:
        std::string baseUrl;
        std::string requestURI;
        std::string requestHost;
        Poco::URI::QueryParameters queryStringParameters;

    };

} }

#endif
