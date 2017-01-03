cmake_minimum_required(VERSION 3.6)
project(cxxurl)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

set(CMAKE_CXX_STANDARD 11)

#find_package(CURL /usr/local/opt/curl REQUIRED)
set(CURL_INCLUDE_DIR /usr/local/opt/curl/include)
set(CURL_LIBRIRIES   /usr/local/opt/curl/lib/libcurl.dylib)




file(GLOB_RECURSE ALL_SRC "src/*.cpp" "include/*.h")

set(SOURCE_FILES main.cpp ${ALL_SRC})

add_executable(cxxurl ${SOURCE_FILES})



message("curl found, include_dir: ${CURL_INCLUDE_DIR}, library: ${CURL_LIBRIRIES}")
include_directories(${CURL_INCLUDE_DIR})
link_directories(${CURL_LIBRIRIES})
target_link_libraries(cxxurl ${CURL_LIBRIRIES})
