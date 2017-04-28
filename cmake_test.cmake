enable_testing()

include_directories(${libcxxurl_SOURCE_DIR})

macro(add_test_target TEST_TARGET TEST_FILE)
    add_executable(${TEST_TARGET} ${TEST_FILE})
    target_link_libraries(${TEST_TARGET} cxxurl_shared ${CURL_LIBRARY})
    ADD_TEST(NAME ${TEST_TARGET} COMMAND ${TEST_TARGET})
endmacro(add_test_target)

macro(add_test_directory TEST_DIRECTORY)
file(GLOB_RECURSE TEST_FILES "${TEST_DIRECTORY}/*.cpp" "${TEST_DIRECTORY}/*.c++"  "${TEST_DIRECTORY}/*.cc" "${TEST_DIRECTORY}/*.c")
foreach(TEST_FILE IN LISTS TEST_FILES)
    get_filename_component(TEST_TARGET ${TEST_FILE} NAME_WE)
    message(STATUS "Found test: ${TEST_TARGET}")
    add_test_target(${TEST_TARGET} ${TEST_FILE})
endforeach(TEST_FILE)
endmacro(add_test_directory)