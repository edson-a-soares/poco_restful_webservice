SET(TEST_UNIT "tests")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(NOT GTEST_FOUND)
    message(WARNING "Failed to find the GTest libraries.")
endif()

file(GLOB_RECURSE TEST_SOURCE_FILES
    ${CMAKE_HOME_DIRECTORY}/test/Domain/*.cpp
    ${CMAKE_HOME_DIRECTORY}/test/Interface/*.cpp
    ${CMAKE_HOME_DIRECTORY}/test/Infrastructure/*.cpp)

add_executable(${TEST_UNIT} ${CMAKE_HOME_DIRECTORY}/test/Runner.cpp ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_UNIT} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT} ${WEBSERVICE_BINARY})

add_test(NAME ${TEST_UNIT} COMMAND "${TEST_UNIT}")
