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

#ifndef Foundation_Http_Router_INCLUDED
#define Foundation_Http_Router_INCLUDED

#include <map>
#include <memory>
#include <string>
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Foundation/Http/RouterAbstractFactoryInterface.h"

namespace Foundation {
namespace Http {


    class Router : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        Poco::Net::HTTPRequestHandler * createRequestHandler (const Poco::Net::HTTPServerRequest &) final;

    protected:
        virtual void loadEndpoints() = 0;
        virtual Poco::Net::HTTPRequestHandler * notFoundErrorHandler();
        virtual std::unique_ptr<RouterAbstractFactoryInterface> getAbstractFactory() = 0;
        void addEndpoint(const std::string & path, const std::string & resourceFactoryName);

    private:
        std::map<std::string, std::string> routingTable = {};

        std::string endpointFactoryKey(const std::string & path);

    };


} }

#endif
