SET(TEST_UNIT "tests")
SET(TESTED_UNIT ${APPLICATION_BINARY_NAME})

enable_testing()

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(NOT GTEST_FOUND)
    message(WARNING "Failed to find the GTest libraries.")
endif()

file(GLOB TEST_SOURCE_FILES_TOP
    ${CMAKE_HOME_DIRECTORY}/test/*.cpp)

file(GLOB_RECURSE TEST_SOURCE_FILES_NESTED
    ${CMAKE_HOME_DIRECTORY}/test/Domain/*.cpp)

set(TEST_SOURCE_FILES ${TEST_SOURCE_FILES_TOP} ${TEST_SOURCE_FILES_NESTED})

add_executable(${TEST_UNIT} ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_UNIT} gtest gtest_main pthread ${TESTED_UNIT})

add_test(NAME ${TEST_UNIT} COMMAND ${TEST_UNIT})
