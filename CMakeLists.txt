cmake_minimum_required(VERSION 3.5.00)
set(CMAKE_CXX_STANDARD 17)
project(ogl-model-loader)

set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)

# Add lib implementation
add_subdirectory(${CMAKE_SOURCE_DIR}/implementation)

set(TESTS triangle-test pbr-test tiny-gltf-test instantiation-test)

foreach(test ${TESTS})
    # Add the executable
    add_subdirectory(${TESTS_DIR}/${test})
endforeach ()
