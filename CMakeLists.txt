cmake_minimum_required(VERSION 3.6)
project(cxxurl_example)

set(CMAKE_CXX_STANDARD 11)

#find_package(CURL /usr/local/opt/curl REQUIRED)
set(CURL_INCLUDE_DIR /usr/local/opt/curl/include)
set(CURL_LIBRIRIES   /usr/local/opt/curl/lib/libcurl.dylib)


set(CXXURL_SRC cxxurl/cxxurl_all.cpp)

find_package(CURL REQUIRED)

#example_get
add_executable(example_get example/example_get.cpp ${CXXURL_SRC})
target_link_libraries(example_get ${CURL_LIBRIRIES})

#example_get_https_disable
add_executable(example_get_https_disable example/example_get_https_disable.cpp ${CXXURL_SRC})
target_link_libraries(example_get_https_disable ${CURL_LIBRIRIES})

#example_get_https_enable
add_executable(example_get_https_enable example/example_get_https_enable.cpp ${CXXURL_SRC})
target_link_libraries(example_get_https_enable ${CURL_LIBRIRIES})

#example_post
add_executable(example_post example/example_post.cpp ${CXXURL_SRC})
target_link_libraries(example_post ${CURL_LIBRIRIES})

#example_download
add_executable(example_download example/example_download.cpp ${CXXURL_SRC})
target_link_libraries(example_download ${CURL_LIBRIRIES})

#example_set_header
add_executable(example_set_header example/example_set_header.cpp ${CXXURL_SRC})
target_link_libraries(example_set_header ${CURL_LIBRIRIES})

#example_cookie
add_executable(example_cookie example/example_cookie.cpp ${CXXURL_SRC})
target_link_libraries(example_cookie ${CURL_LIBRIRIES})

#example_response_header
add_executable(example_response_header example/example_response_header.cpp ${CXXURL_SRC})
target_link_libraries(example_response_header ${CURL_LIBRIRIES})

include_directories(cxxurl ${CURL_INCLUDE_DIR})




