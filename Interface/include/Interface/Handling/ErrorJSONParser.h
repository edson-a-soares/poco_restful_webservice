/*
 * (C) Copyright 2017 Edson (http://edsonaraujosoares.com) and others.
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

#ifndef Web_Service_Interface_Handling_Error_Json_Parser_INCLUDED
#define Web_Service_Interface_Handling_Error_Json_Parser_INCLUDED

#include <string>

namespace Interface {
namespace Handling {


    class ErrorJSONParser
    {
    public:
        ErrorJSONParser();
        ErrorJSONParser(const std::string &);

        std::string toJson(
            const int,
            const std::string &,
            const std::string &,
            const std::string &
        );

    private:
        std::string host;

    };


} }

#endif
