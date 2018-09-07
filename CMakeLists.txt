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

include_directories(src thirdparty/json ${CURL_INCLUDE_DIR})

# Add all examples target
include(cmake/cmake_example.cmake)
add_example_directory(examples)

# Add all test target
include(cmake/cmake_test.cmake)
add_test_directory(tests)

# Add check target for ctest with output-on-failure
include(cmake/cmake_check.cmake)
add_check_target()

file(GLOB_RECURSE CXXURL_FILES "src/cxxurl.cpp" "src/cxxurl/*.h" "thirdparty/json/json.hpp")
add_executable(cxxurl ${CXXURL_FILES})
target_link_libraries(cxxurl ${CURL_LIBRARY})