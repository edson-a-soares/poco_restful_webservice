cmake_minimum_required(VERSION 3.6)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lPocoXML -lPocoJSON -lPocoDataMySQL -lpthread")

SET(CMAKE_SHARED_LIBRARY_PREFIX "")

SET(EXECUTABLE_BINARY_NAME  "webservice")
SET(APPLICATION_BINARY_NAME "poco_restful_webservice")

# Including source code of the project
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/${MODULE_DIRECTORY}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/${MODULE_DIRECTORY}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/${MODULE_DIRECTORY}/build)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/${MODULE_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/${MODULE_DIRECTORY}/bin)

file(GLOB SOURCE_FILES_TOP "${PROJECT_SOURCE_DIR}/*.cpp")
file(GLOB_RECURSE SOURCE_FILES_NESTED
    ${PROJECT_SOURCE_DIR}/Domain/*.cpp
    ${PROJECT_SOURCE_DIR}/Interface/*.cpp
    ${PROJECT_SOURCE_DIR}/Application/*.cpp
    ${PROJECT_SOURCE_DIR}/Infrastructure/*.cpp
)
set(SOURCE_FILES ${SOURCE_FILES_TOP} ${SOURCE_FILES_NESTED})

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(${APPLICATION_BINARY_NAME} SHARED ${SOURCE_FILES})
target_include_directories(${APPLICATION_BINARY_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})

# Poco Library setup
find_library(POCO_NET PocoNet)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_DATA PocoData)
find_library(POCO_FOUNDATION PocoFoundation)

include_directories(${Poco_INCLUDE_DIRS})

find_package(Threads REQUIRED)

target_link_libraries(${APPLICATION_BINARY_NAME} PocoFoundation PocoUtil PocoNet PocoData)

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
