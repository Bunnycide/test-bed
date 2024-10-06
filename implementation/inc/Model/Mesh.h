#ifndef OGL_MODEL_LOADER_MESH_H
#define OGL_MODEL_LOADER_MESH_H

#include "glm/glm.hpp"
#include "Shader/ShaderProgram.h"
#include <iostream>
#include <vector>

#define VERTEX_POSITION_INDEX   0
#define VERTEX_NORMAL_INDEX     1
#define VERTEX_TEX_COORD_INDEX  2
#define VERTEX_TANGENT_INDEX    3
#define VERTEX_BITANGENT_INDEX  4

struct Vertex {
    glm::vec3 Position;
    glm::vec2 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    std::vector<Vertex>         vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture>        textures;

    // Temp vector of floats and unsigned ints
    std::vector<float>          tVertices;
    std::vector<unsigned int>   tIndices;

    // Get the transform mat
    glm::mat4 transformMat;

    // Flags for missing textures
    bool hasNormalMap   = false;
    bool hasSpecularMap = false;
    bool hasHeightMap   = false;

    Mesh(std::vector<Vertex> vertices,
         std::vector<unsigned int> indices,
         std::vector<Texture> textures);
    void draw(ShaderProgram shader);

private:
    unsigned int VAO{}, VBO{}, EBO{};
    void setupMesh();

};

#endif //OGL_MODEL_LOADER_MESH_H
