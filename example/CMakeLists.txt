cmake_minimum_required(VERSION 3.6)
project(cxxurl)

set(CMAKE_CXX_STANDARD 11)

#find_package(CURL /usr/local/opt/curl REQUIRED)
set(CURL_INCLUDE_DIR /usr/local/opt/curl/include)
set(CURL_LIBRIRIES   /usr/local/opt/curl/lib/libcurl.dylib)


file(GLOB_RECURSE ALL_SRC
        main.cpp
        ../cxxurl/cxxurl_all.cpp
        )

set(SOURCE_FILES ${ALL_SRC})

add_executable(cxxurl ${CXXURL_BUILD_TYPE} ${SOURCE_FILES})



include_directories(
        ../cxxurl
        ${CURL_INCLUDE_DIR}
)


link_directories(${CURL_LIBRIRIES})
target_link_libraries(cxxurl ${CURL_LIBRIRIES})


