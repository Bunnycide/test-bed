cmake_minimum_required(VERSION 3.5.00)

set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_FLAGS  -Wno-error=unknown-pragmas)

set(IMP_DIR         ${CMAKE_CURRENT_SOURCE_DIR})
set(EXTERNAL_DIR    ${CMAKE_CURRENT_SOURCE_DIR}/external)
set(IMP_INC_DIR     ${IMP_DIR}/inc)
set(IMP_SRC_DIR     ${IMP_DIR}/src)

# configure assets dir ======================
configure_file(${IMP_INC_DIR}/GeneralUtils/AssetPath.h.in
               ${IMP_INC_DIR}/GeneralUtils/AssetPath.h)
# ===========================================

# ✴.·´¯`·.·★  🎀𝓐𝓭𝓭 𝓖𝓛𝓕𝓦🎀  ★·.·`¯´·.✴
add_subdirectory(${EXTERNAL_DIR}/glfw)
# =============================================

# ✴.·´¯`·.·★  🎀𝓐𝓭𝓭 𝓖𝓛𝓐𝓓🎀  ★·.·`¯´·.✴
add_library(glad                        ${EXTERNAL_DIR}/glad/src/glad.c
        inc/GeneralUtils/AssetPath.h.in)
target_include_directories(glad PUBLIC  ${EXTERNAL_DIR}/glad/include)
# =============================================

# ✴.·´¯`·.·★  🎀𝓐𝓭𝓭 𝓟𝓥𝓡 𝓢𝓓𝓚🎀  ★·.·`¯´·.✴
set(PVR_EGL_LIB     ${EXTERNAL_DIR}/pvr-gles-emulator/lib/libEGL.lib)
set(PVR_GLESv1_LIB  ${EXTERNAL_DIR}/pvr-gles-emulator/lib/libGLES_CM.lib)
set(PVR_GLESv2_LIB  ${EXTERNAL_DIR}/pvr-gles-emulator/lib/libGLESv2.lib)
# ===========================================

# Add Assimp ================================
add_subdirectory(${EXTERNAL_DIR}/assimp)
# ===========================================

# Add glm ===================================
add_subdirectory(${EXTERNAL_DIR}/glm)
# ===========================================

# Add stb ===================================
add_library(stb ${EXTERNAL_DIR}/stb/stb_image_implementation.cpp)
# ===========================================

# ✴.·´¯`·.·★  🎀𝓐𝓭𝓭 Log lib 🎀  ★·.·`¯´·.✴
add_library(log ${IMP_DIR}/src/Log/Log.cpp)
target_include_directories(log PUBLIC ${IMP_INC_DIR})
target_compile_definitions(log PUBLIC CMAKE_C_STANDARD=C99)
# ===========================================

# json library
add_subdirectory(${EXTERNAL_DIR}/json)

# Target link libraries list
set(LINK_LIBS glfw glad log assimp glm stb nlohmann_json)

add_library(implementation  ${IMP_SRC_DIR}/Window/Window.cpp
                            ${IMP_SRC_DIR}/Application/Application.cpp
                            ${IMP_SRC_DIR}/GeneralUtils/fileutils.cpp
                            ${IMP_SRC_DIR}/GeneralUtils/macros.cpp
                            ${IMP_SRC_DIR}/Shader/ShaderProgram.cpp
                            ${IMP_SRC_DIR}/Shader/utils.cpp
                            ${IMP_SRC_DIR}/Log/Log.cpp
                            ${IMP_SRC_DIR}/Model/Mesh.cpp
                            ${IMP_SRC_DIR}/Model/Model.cpp
                            ${IMP_SRC_DIR}/Model/utils.cpp
                            ${IMP_SRC_DIR}/SkyBox/skybox.cpp
                            ${IMP_SRC_DIR}/SkyBox/util.cpp
                            ${IMP_SRC_DIR}/Camera/Camera.cpp
                            ${IMP_SRC_DIR}/Texture/Texture2D.cpp
                            ${IMP_SRC_DIR}/gltfLoader/gltfLoader.cpp
                            ${IMP_SRC_DIR}/gltfLoader/Scene.cpp
                            ${IMP_SRC_DIR}/gltfLoader/Model.cpp
                            ${IMP_SRC_DIR}/Texture/util.cpp)

# Include dirs
target_include_directories(implementation 
                                PUBLIC
                                        ${IMP_INC_DIR}
                                        ${EXTERNAL_DIR}/glfw/include
                                        ${EXTERNAL_DIR}/glad/include
                                        ${EXTERNAL_DIR}/assimp/includ
                                        ${EXTERNAL_DIR}/glm      
                                        ${EXTERNAL_DIR}/stb
                                        ${EXTERNAL_DIR}/json/include      )

# Link to target
target_link_libraries(implementation ${LINK_LIBS})
