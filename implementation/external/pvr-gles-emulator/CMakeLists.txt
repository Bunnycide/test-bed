cmake_minimum_required(VERSION 3.25.0)

message("-- Linking gles emulator")

add_library(libGLESv2   ${CMAKE_CURRENT_SOURCE_DIR}/lib/libGLESv2.dll)
add_library(libEGL      ${CMAKE_CURRENT_SOURCE_DIR}/lib/libEGL.dll)
set_target_properties(libGLESv2    PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(libEGL       PROPERTIES LINKER_LANGUAGE CXX)