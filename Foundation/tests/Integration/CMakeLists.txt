SET(TEST_TYPE_AND_DIRECTORY_NAME "Integration")
SET(TEST_UNIT ${MODULE_NAME}${TEST_TYPE_AND_DIRECTORY_NAME}Tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(NOT GTEST_FOUND)
    message(WARNING "Failed to find the GTest libraries.")
endif()

set(TESTS_INCLUDE_FILES ${CMAKE_HOME_DIRECTORY}/${COMPONENT_NAME}/tests/${TEST_TYPE_AND_DIRECTORY_NAME}/)

file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_HOME_DIRECTORY}/${MODULE_NAME}/tests/${TEST_TYPE_AND_DIRECTORY_NAME}/*.cpp)

# It makes the Resources directory path available into the C++ source code as a constant.
add_definitions(-DTESTS_DATA_PATH="${CMAKE_HOME_DIRECTORY}/${MODULE_NAME}/tests/data/")

add_executable(${TEST_UNIT} ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_UNIT} gtest gtest_main pthread ${MODULE_BINARY_NAME})
target_include_directories(${TEST_UNIT} PUBLIC ${TESTS_INCLUDE_FILES})

add_test(NAME ${TEST_UNIT} COMMAND ${TEST_UNIT})
