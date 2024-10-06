//
// Created by jaeb on 30/06/24.
//

#ifndef GLTFSTRUCTS_H
#define GLTFSTRUCTS_H

#include "glm/glm.hpp"

typedef struct pbr_metallic_roughness_t {
    glm::vec3 base_color_factor;
    int metallic_factor = 0;
    float roughness_factor = 0.0f;
} pbr_metallic_roughness;

typedef struct material_t {
    const char* name = nullptr;
    bool double_sided = false;
    glm::vec3 emissive_factor{};

    pbr_metallic_roughness pbrmr{};
} material;

typedef struct mesh_t {
    const char* name = nullptr;
    glm::vec3* position = nullptr;
    glm::vec3* normal = nullptr;
    glm::vec2* tex_coords = nullptr;
    uint16_t* indices = nullptr;
    material mat{};
} mesh;

typedef struct node_t {
    const char* name;
    glm::vec4 rotation{};
    glm::vec4 translation{};
} node;

typedef struct scene_t {
    const char* name = nullptr;
    node* nodes = nullptr;
} scene;

typedef struct asset_t {
    const char* gltf_version{};
    unsigned int default_scene{0};
    scene* scenes = nullptr;
} asset;


#endif //GLTFSTRUCTS_H
