cmake_minimum_required(VERSION 2.6)
project(cxxurl_example)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

if(!CURL_FOUND)
    message(FATAL_ERROR  "CURL_NOT_FOUND")
endif()

include_directories(${libcxxurl_SOURCE_DIR} ${CURL_INCLUDE_DIR})

macro(add_example_target EXAMPLE_TARGET EXAMPLE_FILE)
    add_executable(${EXAMPLE_TARGET} ${EXAMPLE_FILE})
    target_link_libraries(${EXAMPLE_TARGET} cxxurl_shared ${CURL_LIBRARY})
    ADD_TEST(NAME ${EXAMPLE_TARGET} COMMAND ${EXAMPLE_TARGET})
endmacro(add_example_target)

file(GLOB_RECURSE EXAMPLE_FILES "example_*.cpp" "example_*.c++"  "example_*.cc" "example_*.c")

foreach(EXAMPLE_FILE IN LISTS EXAMPLE_FILES)
    get_filename_component(EXAMPLE_TARGET ${EXAMPLE_FILE} NAME_WE)
    message(STATUS "Found example: ${EXAMPLE_TARGET}")
    add_example_target(${EXAMPLE_TARGET} ${EXAMPLE_FILE})
endforeach(EXAMPLE_FILE)