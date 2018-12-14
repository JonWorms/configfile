cmake_minimum_required(VERSION 3.7.2)
project(configfile)

if(APPLE)
	set(CMAKE_CXXFLAGS "${CMAKE_CXXFLAGS} -std=c++14")
endif()


include_directories(${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/include")


set(${PROJECT_NAME}_INCLUDE_DIRS ${PROJECT_BINARY_DIR} "${PROJECT_SOURCE_DIR}/include"
CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

 

add_library(configfile src/config_file.cpp)
add_executable(demo src/demo.cpp)


target_link_libraries(demo configfile)


enable_testing()


set(CFG_KEY_1 "key1")
set(CFG_VALUE_1 "value1")
set(CFG_KEY_2 "key2")
set(CFG_VALUE_2 "value2")
set(CFG_KEY_3 "key3")
set(CFG_VALUE_3 "value3")

configure_file(test.cfg.in "${PROJECT_BINARY_DIR}/test.cfg")
configure_file(expected.cfg.in "${PROJECT_BINARY_DIR}/expected.cfg")

#test load/count
add_test(TEST_CFG_FILE_LOAD demo test.cfg "-c")
set_tests_properties(TEST_CFG_FILE_LOAD PROPERTIES PASS_REGULAR_EXPRESSION "^4")

# test getting values
add_test(TEST_GET_1 demo test.cfg "-g" "key1")
set_tests_properties(TEST_GET_1 PROPERTIES PASS_REGULAR_EXPRESSION "^value1")

add_test(TEST_GET_2 demo test.cfg "-g" "key2")
set_tests_properties(TEST_GET_2 PROPERTIES PASS_REGULAR_EXPRESSION "^value2")

add_test(TEST_GET_3 demo test.cfg "-g" "key3")
set_tests_properties(TEST_GET_3 PROPERTIES PASS_REGULAR_EXPRESSION "^value3")


# test commiting to file
add_test(TEST_COMMIT demo "test.cfg" "-w")
add_test(TEST_COMMIT_RESULT cmp "test.cfg" "expected.cfg")
set_tests_properties(TEST_COMMIT_RESULT PROPERTIES PASS_REGULAR_EXPRESSION "")

# test setting value
add_test(TEST_WRITE_1 demo "test.cfg" "-s" "key1" "changedValue1")
add_test(TEST_WRITE_RESULT_1 demo "test.cfg" "-g" "key1")
set_tests_properties(TEST_WRITE_RESULT_1 PROPERTIES PASS_REGULAR_EXPRESSION "^changedValue1")

add_test(TEST_WRITE_NEW demo test.cfg "-s" "newKey1" "newValue1")
add_test(TEST_WRITE_NEW_RESULT demo test.cfg "-g" "newKey1")
set_tests_properties(TEST_WRITE_NEW_RESULT PROPERTIES PASS_REGULAR_EXPRESSION "^newValue1")
