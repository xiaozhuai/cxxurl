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


# uninstall target
configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
        IMMEDIATE @ONLY)

add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)


# test target
include_directories(${libcxxurl_SOURCE_DIR} ${CURL_INCLUDE_DIR})
enable_testing()

macro(add_test_target TEST_TARGET TEST_FILE)
    add_executable(${TEST_TARGET} ${TEST_FILE})
    target_link_libraries(${TEST_TARGET} cxxurl_shared ${CURL_LIBRARY})
    ADD_TEST(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
endmacro(add_test_target)

file(GLOB_RECURSE TEST_FILES "tests/Test*.cpp" "tests/Test*.c++"  "tests/Test*.cc" "tests/Test*.c")

foreach(TEST_FILE IN LISTS TEST_FILES)
    get_filename_component(TEST_TARGET ${TEST_FILE} NAME_WE)
    message(STATUS "Found test: ${TEST_TARGET}")
    add_test_target(${TEST_TARGET} ${TEST_FILE})
endforeach(TEST_FILE)

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>")
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure)
endif()