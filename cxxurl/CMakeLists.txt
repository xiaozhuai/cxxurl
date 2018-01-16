cmake_minimum_required(VERSION 2.6)
project(libcxxurl)

set(CMAKE_CXX_STANDARD 11)

set(LIBCXXURL_VERSION 0.4)
set(LIBCXXURL_SO_VERSION 0)

set(CMAKE_MACOSX_RPATH 0)

find_package(CURL REQUIRED)

if(!CURL_FOUND)
    message(FATAL_ERROR  "CURL_NOT_FOUND")
endif()

include_directories(${CURL_INCLUDE_DIR})

file(GLOB_RECURSE SOURCE_FILES "cxxurl/*.cpp")

add_library(cxxurl_static STATIC ${SOURCE_FILES})
add_library(cxxurl_shared SHARED ${SOURCE_FILES})

set_target_properties(cxxurl_static PROPERTIES OUTPUT_NAME cxxurl)
set_target_properties(cxxurl_shared PROPERTIES OUTPUT_NAME cxxurl)

set_target_properties(cxxurl_shared PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(cxxurl_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    add_definitions(-DCXXURL_DEBUG)
else()
    remove_definitions(-DCXXURL_DEBUG)
endif()

add_definitions(-DLIBCXXURL_VERSION=${LIBCXXURL_VERSION})
add_definitions(-DLIBCXXURL_SO_VERSION=${LIBCXXURL_SO_VERSION})


set_target_properties(cxxurl_shared PROPERTIES VERSION ${LIBCXXURL_VERSION} SOVERSION ${LIBCXXURL_SO_VERSION})

target_link_libraries(cxxurl_static ${CURL_LIBRARY})
target_link_libraries(cxxurl_shared ${CURL_LIBRARY})

SET(CMAKE_INSTALL_PREFIX /usr/local)

file(GLOB_RECURSE HEADER_FILES "cxxurl/*.h")

INSTALL(FILES ${HEADER_FILES} DESTINATION include/cxxurl)
INSTALL(TARGETS cxxurl_shared cxxurl_static DESTINATION lib)