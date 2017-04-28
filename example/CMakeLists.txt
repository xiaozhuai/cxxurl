cmake_minimum_required(VERSION 2.6)
project(cxxurl_example)

set(CMAKE_CXX_STANDARD 11)

find_package(CURL REQUIRED)

if(!CURL_FOUND)
    message(FATAL_ERROR  "CURL_NOT_FOUND")
endif()

include_directories(${libcxxurl_SOURCE_DIR} ${CURL_INCLUDE_DIR})

#example_get
add_executable(example_get example_get.cpp)
target_link_libraries(example_get cxxurl_shared ${CURL_LIBRARY})

#example_get_https_disable
add_executable(example_get_https_disable example_get_https_disable.cpp)
target_link_libraries(example_get_https_disable cxxurl_shared ${CURL_LIBRARY})

#example_get_https_enable
add_executable(example_get_https_enable example_get_https_enable.cpp)
target_link_libraries(example_get_https_enable cxxurl_shared ${CURL_LIBRARY})

#example_post
add_executable(example_post example_post.cpp)
target_link_libraries(example_post cxxurl_shared ${CURL_LIBRARY})

#example_download
add_executable(example_download example_download.cpp)
target_link_libraries(example_download cxxurl_shared ${CURL_LIBRARY})

#example_set_header
add_executable(example_set_header example_set_header.cpp)
target_link_libraries(example_set_header cxxurl_shared ${CURL_LIBRARY})

#example_cookie
add_executable(example_cookie example_cookie.cpp)
target_link_libraries(example_cookie cxxurl_shared ${CURL_LIBRARY})

#example_response_header
add_executable(example_response_header example_response_header.cpp)
target_link_libraries(example_response_header cxxurl_shared ${CURL_LIBRARY})

#example_use_curl_option
add_executable(example_use_curl_option example_use_curl_option.cpp)
target_link_libraries(example_use_curl_option cxxurl_shared ${CURL_LIBRARY})

#example_without_request_builder
add_executable(example_without_request_builder example_without_request_builder.cpp)
target_link_libraries(example_without_request_builder cxxurl_shared ${CURL_LIBRARY})




