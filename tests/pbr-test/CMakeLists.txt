cmake_minimum_required(VERSION 3.5.00)

set(TEST_NAME pbr-test)

add_executable(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/src/test.cpp)

target_include_directories(${TEST_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

target_link_libraries(${TEST_NAME} implementation)
