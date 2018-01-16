cmake_minimum_required(VERSION 2.6)
project(cxxurl)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

if(CURL_FOUND)
    message(STATUS "CURL_FOUND: ${CURL_FOUND}")
    message(STATUS "CURL_INCLUDE_DIR: ${CURL_INCLUDE_DIR}")
    message(STATUS "CURL_LIBRARY: ${CURL_LIBRARY}")
else()
    message(FATAL_ERROR  "CURL_NOT_FOUND")
endif()

add_subdirectory(cxxurl)

# Add all examples target
include(cmake/cmake_example.cmake)
add_example_directory(examples)

# Add all test target
include(cmake/cmake_test.cmake)
add_test_directory(tests)

# Add check target for ctest with output-on-failure
include(cmake/cmake_check.cmake)
add_check_target()

# Add uninstall target
include(cmake/cmake_uninstall.cmake)
add_uninstall_target()