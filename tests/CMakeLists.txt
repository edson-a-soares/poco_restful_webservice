SET(TESTS_UNIT "tests")

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(NOT GTEST_FOUND)
    message(WARNING "Failed to find the GTest libraries.")
endif()

file(GLOB_RECURSE TESTS_SOURCE_FILES ${CMAKE_HOME_DIRECTORY}/tests/*.cpp)

add_executable(${TESTS_UNIT} ${CMAKE_HOME_DIRECTORY}/tests/Runner.cpp ${TESTS_SOURCE_FILES})
target_link_libraries(${TESTS_UNIT} gtest gtest_main ${CMAKE_THREAD_LIBS_INIT} ${WEBSERVICE_BINARY})

add_test(NAME ${TESTS_UNIT} COMMAND "${TESTS_UNIT}")
