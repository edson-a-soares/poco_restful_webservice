cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# It sets default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wextra -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        --coverage -O -g -rdynamic -Wshadow -Wunused-parameter -Wunused-variable -Wdelete-non-virtual-dtor -Wfatal-errors \
        -Woverloaded-virtual -Wunreachable-code -Wno-unused -Wundef -Wl,--no-undefined -Wl,--no-allow-shlib-undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -w -Wl,--discard-all")

SET(CMAKE_SHARED_LIBRARY_PREFIX "")

SET(WEBSERVICE_CLI  "webservice")
SET(WEBSERVICE_BINARY "poco_restful_webservice")

# application's directories settings
set(WEBSERVICE_HOSTING_DIRECTORY_NAME poco_webservice)
set(WEBSERVICE_BINARY_DIRECTORY ${CMAKE_INSTALL_PREFIX}/bin)
set(WEBSERVICE_LIBRARY_DIRECTORY ${CMAKE_INSTALL_PREFIX}/lib)
set(WEBSERVICE_CONFIG_DIRECTORY ${CMAKE_INSTALL_PREFIX}/etc/${WEBSERVICE_HOSTING_DIRECTORY_NAME})

# Including source code of the project
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

file(GLOB_RECURSE SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(${WEBSERVICE_BINARY} SHARED ${SOURCE_FILES})
target_include_directories(${WEBSERVICE_BINARY} PUBLIC ${PROJECT_INCLUDE_DIR})
set_target_properties(${MODULE_BINARY_NAME} PROPERTIES COMPILE_FLAGS "--coverage" LINK_FLAGS "-lgcov --coverage")

# Poco Library setup
find_library(Poco_LIBRARIES NAMES PocoFoundation PocoJSON PocoUtil PocoNet PocoSQL)

if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
target_link_libraries(${WEBSERVICE_BINARY} PocoFoundation PocoJSON PocoUtil PocoNet PocoSQL PocoSQLMySQL)

find_package(Threads REQUIRED)

# Handling options
option(ENABLE_TESTS
        "Set to OFF|ON (default: OFF) to control build of API tests" OFF)

option(ENABLE_STANDALONE_SERVICE
        "Set to OFF|ON (default: ON) to control build of API as standalone service" ON)

if (ENABLE_STANDALONE_SERVICE)
    add_executable(${WEBSERVICE_CLI} ${PROJECT_SOURCE_DIR}/main.cpp)
    target_link_libraries(${WEBSERVICE_CLI} ${WEBSERVICE_BINARY})

    message(STATUS "Building API with standalone service support.")
elseif ()
    message(STATUS "Building without standalone service support.")
endif ()

if (ENABLE_TESTS)
    add_subdirectory(tests)

    message(STATUS "Building with tests")
elseif ()
    message(STATUS "Building without tests")
endif ()

#### installation ###################################

# install (DIRECTORY "${CMAKE_HOME_DIRECTORY}/data/settings/"
#        DESTINATION "${WEBSERVICE_CONFIG_DIRECTORY}" FILES_MATCHING PATTERN "*.ini")

install(TARGETS ${WEBSERVICE_BINARY} DESTINATION ${WEBSERVICE_LIBRARY_DIRECTORY})
# install(TARGETS ${WEBSERVICE_CLI} DESTINATION ${WEBSERVICE_BINARY_DIRECTORY} OPTIONAL)


