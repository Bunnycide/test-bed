//
// Created by jaeb on 30/06/24.
//

#ifndef MODEL_H
#define MODEL_H

#include <Shader/ShaderProgram.h>

typedef struct Texture_t {
    std::string uri;
    int width, height, channels;
    unsigned char* data;
} Texture;

typedef struct Mesh_t {
    unsigned int vaoID;
    unsigned int vboID;
    std::vector<Texture> textures;
} Mesh;

typedef struct Material_t {
    std::string name;
    glm::vec4 baseColorFactor;
    float metallicFactor;
    float roughnessFactor;
    int baseColorTextureIndex;
    int metallicRoughnessTextureIndex;
} Material;

class Model {
public:
    explicit Model();
    void draw(ShaderProgram& shader_program);
private:
    std::vector<Mesh*> meshlist;
};



#endif //MODEL_H
