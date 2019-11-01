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

#ifndef Foundation_Application_AbstractConfigurationFile_INCLUDED
#define Foundation_Application_AbstractConfigurationFile_INCLUDED

#include <string>
#include "Foundation/Application/Environment.h"
#include "Foundation/Application/ConfigurationFileInterface.h"

namespace Foundation {
namespace Application {


    /*!
     * It defines the basics for a configuration file.
     * A derived class of AbstractConfiguration just need to specify the name of the configuration file.
     *
     * The constant APPLICATION_HOSTING_DIRECTORY_PATH is defined on the CMakeLists file.
     */
    class AbstractConfigurationFile : public ConfigurationFileInterface
    {
    public:
        explicit AbstractConfigurationFile(const std::string & fileName);
        virtual ~AbstractConfigurationFile() = default;
        std::string path() const final;

    protected:
        void basePath(const std::string &);

    private:
        std::string _basePath;
        std::string _fileName;

    };


} }

#endif
