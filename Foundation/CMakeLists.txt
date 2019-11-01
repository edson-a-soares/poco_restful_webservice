#-----------------------------------------------------------------------------
# It defines module information.
#-----------------------------------------------------------------------------
set(MODULE_NAME "Foundation")

# Component's binary name.
set(MODULE_BINARY_NAME ${WEB_SERVICE_MODULE_PREFIX}_${MODULE_NAME})

#-----------------------------------------------------------------------------
# Component Source Code Handling
#-----------------------------------------------------------------------------
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/${MODULE_NAME}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/${MODULE_NAME}/src)

file(GLOB_RECURSE FOUNDATION_MODULE_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

# It makes the application hosting directory path available into the C++ source code as a constant.
add_definitions(-DAPPLICATION_HOSTING_DIRECTORY_PATH="${CMAKE_HOME_DIRECTORY}")
add_definitions(-DAPPLICATION_HOSTING_DIRECTORY_NAME="${WEB_SERVICE_HOSTING_DIRECTORY_NAME}")

add_library(${MODULE_BINARY_NAME} SHARED ${FOUNDATION_MODULE_SOURCE_FILES})
target_include_directories(${MODULE_BINARY_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})

#-----------------------------------------------------------------------------
# Handle application dependencies
#-----------------------------------------------------------------------------
set(DEPENDENCIES_LIBS "")

#-----------------------------------------------------------------------------
# Poco libraries setup
#-----------------------------------------------------------------------------
find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_JSON PocoJSON)
find_library(POCO_XML PocoXML)
find_library(POCO_NET PocoNet)
find_library(POCO_NET PocoData)

include_directories(${Poco_INCLUDE_DIRS})
set(DEPENDENCIES_LIBS ${DEPENDENCIES_LIBS} ${POCO_FOUNDATION} ${POCO_JSON} ${POCO_XML} ${POCO_UTIL} ${POCO_NET})

#-----------------------------------------------------------------------------
# Threads
#-----------------------------------------------------------------------------
find_package(Threads REQUIRED)

# it links all dependencies to the application
target_link_libraries(${MODULE_BINARY_NAME} ${DEPENDENCIES_LIBS} -lpthread PocoData PocoDataMySQL PocoDataSQLite)

#-----------------------------------------------------------------------------
# Handle module optional parts
#-----------------------------------------------------------------------------
if (ENABLE_TESTS)
    add_subdirectory(tests)
    message(STATUS "Building ${MODULE_NAME} with tests")
elseif ()
    message(STATUS "Building ${MODULE_NAME} without tests")
endif ()

#-----------------------------------------------------------------------------
# Handle module instalation
#-----------------------------------------------------------------------------
install(TARGETS ${MODULE_BINARY_NAME} DESTINATION ${WEB_SERVICE_LIBRARY_DIRECTORY})
