#ifndef GLTFLOADER_H
#define GLTFLOADER_H

#include <fstream>
#include <nlohmann/json.hpp>
#include <Log/Log.h>
#include <glad/glad.h>
#include <glm/glm.hpp>

#include "gltfLoader/gltfstructs.h"

#define COMPONENT_TYPE_SIGNED_BYTE      5120
#define COMPONENT_TYPE_UNSIGNED_BYTE    5121
#define COMPONENT_TYPE_SIGNED_SHORT     5122
#define COMPONENT_TYPE_UNSIGNED_SHORT   5123
#define COMPONENT_TYPE_UNSIGNED_INT     5125
#define COMPONENT_TYPE_FLOAT            5126

#define NUM_COMPONENTS_SCALAR   1
#define NUM_COMPONENTS_VEC2     2
#define NUM_COMPONENTS_VEC3     3
#define NUM_COMPONENTS_VEC4     4
#define NUM_COMPONENTS_MAT2     4
#define NUM_COMPONENTS_MAT3     9
#define NUM_COMPONENTS_MAT4     16

using json = nlohmann::json;

asset loadGltf(const std::string& );
void loadAsset(json& , asset& );


#endif // GLTFLOADER_H
