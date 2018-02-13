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

#ifndef Web_Service_Interface_Handling_JSONAPI_IJson_API_Error_INCLUDED
#define Web_Service_Interface_Handling_JSONAPI_IJson_API_Error_INCLUDED

#include <string>

namespace Interface {
namespace Handling {


    /*!
     * It builds a error in the Json API error format.
     *
     * @see http://jsonapi.org
     */
    class IJsonAPIError
    {
    public:

        virtual void withStatusCode(int) = 0;
        virtual void withType(const std::string &) = 0;
        virtual void withDetails(const std::string &) = 0;

        /**
         * Adds a pointer to the source of the error.
         *
         * @param pointer A URL to the source of the error.
         */
        virtual void sourceAt(const std::string &) = 0;

    };


} }

#endif
