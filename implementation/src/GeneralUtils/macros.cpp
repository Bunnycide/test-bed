//
// Created by a00874817 on 23/06/2024.
//
#include "GeneralUtils/macros.h"

std::string glEnumToString(GLenum enumVal) {
    static const std::unordered_map<GLenum, std::string> glEnumMap = {
            // Buffer Types
            {34962, "GL_ARRAY_BUFFER"},
            {34963, "GL_ELEMENT_ARRAY_BUFFER"},
            {35051, "GL_PIXEL_PACK_BUFFER"},
            {35052, "GL_PIXEL_UNPACK_BUFFER"},
            {35345, "GL_UNIFORM_BUFFER"},

            // Shader Types
            {35633, "GL_VERTEX_SHADER"},
            {35632, "GL_FRAGMENT_SHADER"},
            {36313, "GL_GEOMETRY_SHADER"},
            {37305, "GL_COMPUTE_SHADER"},
            {36488, "GL_TESS_CONTROL_SHADER"},
            {36487, "GL_TESS_EVALUATION_SHADER"},

            // Texture Types
            {3552, "GL_TEXTURE_1D"},
            {3553, "GL_TEXTURE_2D"},
            {32879, "GL_TEXTURE_3D"},
            {34067, "GL_TEXTURE_CUBE_MAP"},

            // Texture Parameters
            {10241, "GL_TEXTURE_MIN_FILTER"},
            {10240, "GL_TEXTURE_MAG_FILTER"},
            {10242, "GL_TEXTURE_WRAP_S"},
            {10243, "GL_TEXTURE_WRAP_T"},

            // Texture Filtering
            {9728, "GL_NEAREST"},
            {9729, "GL_LINEAR"},
            {9984, "GL_NEAREST_MIPMAP_NEAREST"},
            {9985, "GL_LINEAR_MIPMAP_NEAREST"},
            {9986, "GL_NEAREST_MIPMAP_LINEAR"},
            {9987, "GL_LINEAR_MIPMAP_LINEAR"},

            // Primitive Types
            {0, "GL_POINTS"},
            {1, "GL_LINES"},
            {3, "GL_LINE_STRIP"},
            {2, "GL_LINE_LOOP"},
            {4, "GL_TRIANGLES"},
            {5, "GL_TRIANGLE_STRIP"},
            {6, "GL_TRIANGLE_FAN"},

            // Framebuffer Attachments
            {36064, "GL_COLOR_ATTACHMENT0"},
            {36096, "GL_DEPTH_ATTACHMENT"},
            {36128, "GL_STENCIL_ATTACHMENT"},

            // Clear Buffer Mask
            {16384, "GL_COLOR_BUFFER_BIT"},
            {256, "GL_DEPTH_BUFFER_BIT"},
            {1024, "GL_STENCIL_BUFFER_BIT"},

            // Blend Functions
            {0, "GL_ZERO"},
            {1, "GL_ONE"},
            {768, "GL_SRC_COLOR"},
            {769, "GL_ONE_MINUS_SRC_COLOR"},
            {774, "GL_DST_COLOR"},
            {775, "GL_ONE_MINUS_DST_COLOR"},
            {770, "GL_SRC_ALPHA"},
            {771, "GL_ONE_MINUS_SRC_ALPHA"},
            {772, "GL_DST_ALPHA"},
            {773, "GL_ONE_MINUS_DST_ALPHA"},

            // Depth Functions
            {512, "GL_NEVER"},
            {513, "GL_LESS"},
            {514, "GL_EQUAL"},
            {515, "GL_LEQUAL"},
            {516, "GL_GREATER"},
            {517, "GL_NOTEQUAL"},
            {518, "GL_GEQUAL"},
            {519, "GL_ALWAYS"},


            // Data Types
            {5126, "GL_FLOAT"},
            {35664, "GL_FLOAT_VEC2"},
            {35665, "GL_FLOAT_VEC3"},
            {35666, "GL_FLOAT_VEC4"},
            {35674, "GL_FLOAT_MAT2"},
            {35675, "GL_FLOAT_MAT3"},
            {35676, "GL_FLOAT_MAT4"},
            {35685, "GL_FLOAT_MAT2x3"},
            {35686, "GL_FLOAT_MAT2x4"},
            {35687, "GL_FLOAT_MAT3x2"},
            {35688, "GL_FLOAT_MAT3x4"},
            {35689, "GL_FLOAT_MAT4x2"},
            {35690, "GL_FLOAT_MAT4x3"},
            {5124, "GL_INT"},
            {35667, "GL_INT_VEC2"},
            {35668, "GL_INT_VEC3"},
            {35669, "GL_INT_VEC4"},
            {5125, "GL_UNSIGNED_INT"},
            {36294, "GL_UNSIGNED_INT_VEC2"},
            {36295, "GL_UNSIGNED_INT_VEC3"},
            {36296, "GL_UNSIGNED_INT_VEC4"},
            {5130, "GL_DOUBLE"},
            {36860, "GL_DOUBLE_VEC2"},
            {36861, "GL_DOUBLE_VEC3"},
            {36862, "GL_DOUBLE_VEC4"},
            {36678, "GL_DOUBLE_MAT2"},
            {36679, "GL_DOUBLE_MAT3"},
            {36680, "GL_DOUBLE_MAT4"},
            {36685, "GL_DOUBLE_MAT2x3"},
            {36686, "GL_DOUBLE_MAT2x4"},
            {36681, "GL_DOUBLE_MAT3x2"},
            {36684, "GL_DOUBLE_MAT3x4"},
            {36682, "GL_DOUBLE_MAT4x2"},
            {36683, "GL_DOUBLE_MAT4x3"}
    };

    auto it = glEnumMap.find(enumVal);
    if (it != glEnumMap.end()) {
        return it->second;
    } else {
        return "Unknown Enum";
    }
}