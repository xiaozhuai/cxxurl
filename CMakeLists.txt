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
add_subdirectory(example)



