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

#ifndef Web_Service_Interface_Router_INCLUDED
#define Web_Service_Interface_Router_INCLUDED

#include <map>
#include <string>
#include "Resource/Factory/IFactory.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"

namespace Interface {


    class Router : public Poco::Net::HTTPRequestHandlerFactory
    {
    public:
        Router();

        void addRoute(const std::string &, const std::string &);
        Poco::Net::HTTPRequestHandler * createRequestHandler (const Poco::Net::HTTPServerRequest & request);

    private:
        void init();
        std::map<std::string, std::string> routingTable;
        Poco::Net::HTTPRequestHandler * getResource(const std::string &);

    };

}

#endif
