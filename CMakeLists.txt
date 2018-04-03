cmake_minimum_required(VERSION 3.7)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# It sets default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wextra -Wall -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        -O -g -rdynamic -Wshadow -Wunused-parameter -Wunused-variable -Wdelete-non-virtual-dtor -Wfatal-errors \
        -Woverloaded-virtual -Wunreachable-code -Wno-unused -Wundef -Wl,--no-undefined -Wl,--no-allow-shlib-undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -w -Wl,--discard-all")

SET(CMAKE_SHARED_LIBRARY_PREFIX "")

SET(EXECUTABLE_BINARY_NAME  "webservice")
SET(APPLICATION_BINARY_NAME "poco_restful_webservice")

# Including source code of the project
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

file(GLOB_RECURSE SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/Domain/*.cpp
    ${PROJECT_SOURCE_DIR}/Interface/*.cpp
    ${PROJECT_SOURCE_DIR}/Application/*.cpp
    ${PROJECT_SOURCE_DIR}/Infrastructure/*.cpp)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(${APPLICATION_BINARY_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${APPLICATION_BINARY_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})

# Poco Library setup
find_library(Poco_LIBRARIES NAMES PocoFoundation PocoJSON PocoUtil PocoNet PocoData)

if(NOT ${Poco_FOUND})
    message(FATAL_ERROR "Poco C++ Libraries not found.")
endif()

include_directories(${Poco_INCLUDE_DIRS})
target_link_libraries(${APPLICATION_BINARY_NAME} PocoFoundation PocoJSON PocoUtil PocoNet PocoData PocoDataMySQL)

find_package(Threads REQUIRED)

# Handling options
option(ENABLE_TESTS
        "Set to OFF|ON (default: OFF) to control build of API tests" OFF)

option(ENABLE_STANDALONE_SERVICE
        "Set to OFF|ON (default: ON) to control build of API as standalone service" ON)

if (ENABLE_STANDALONE_SERVICE)
    add_executable(${EXECUTABLE_BINARY_NAME} ${PROJECT_SOURCE_DIR}/main.cpp)
    target_link_libraries(${EXECUTABLE_BINARY_NAME} ${APPLICATION_BINARY_NAME})

    message(STATUS "Building API with standalone service support.")
elseif ()
    message(STATUS "Building without standalone service support.")
endif ()

if (ENABLE_TESTS)
    add_subdirectory(test)

    message(STATUS "Building with tests")
elseif ()
    message(STATUS "Building without tests")
endif ()
