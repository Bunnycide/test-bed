//
// Created by a00874817 on 23/06/2024.
//

#ifndef OGL_MODEL_LOADER_UTILS_H
#define OGL_MODEL_LOADER_UTILS_H

#include <vector>
#include <string>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "Log/Log.h"

#include "glm/glm.hpp"

glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from);

#endif //OGL_MODEL_LOADER_UTILS_H
