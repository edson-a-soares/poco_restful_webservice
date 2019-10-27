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

#ifndef File_CORSHeadersHandler_INCLUDED
#define File_CORSHeadersHandler_INCLUDED

#include <map>
#include <string>
#include <memory>
#include "Foundation/Http/CORSHeadersInterface.h"
#include "Foundation/IO/JSONFileReaderInterface.h"

namespace File {


    class CORSHeadersFromJSONFile :
        public Foundation::Http::CORSHeadersInterface
    {
    public:
        explicit CORSHeadersFromJSONFile(std::unique_ptr<Foundation::IO::JSONFileReaderInterface>);
        std::map<std::string, std::string> headers() override;

    private:
        std::map<std::string, std::string> _headers;
        std::unique_ptr<Foundation::IO::JSONFileReaderInterface> _fileReader;

    };


}

#endif
