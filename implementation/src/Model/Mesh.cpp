#include <Model/Mesh.h>

#include <utility>
#include "Model/utils.h"
#include "Log/Log.h"

void Mesh::draw(ShaderProgram shader) {
    shader.use();

    unsigned int diffuseIndex = 0;
    unsigned int normalIndex = 0;
    unsigned int specularIndex = 0;
    unsigned int heightIndex = 0;

    for (unsigned int i = 0; i < textures.size(); i++) {
        glActiveTexture(GL_TEXTURE0 + i);
        std::string name = textures[i].type;

        if (name == "texture_diffuse") {
            shader.set("material.diffuseMaps[" + std::to_string(diffuseIndex) + "]", i);
            diffuseIndex++;
        }
        else if (name == "texture_specular" & hasSpecularMap) {
            shader.set("material.specularMaps[" + std::to_string(specularIndex) + "]", i);
            specularIndex++;
        }
        else if (name == "texture_normal" & hasNormalMap) {
            shader.set("material.normalMaps[" + std::to_string(normalIndex) + "]", i);
            normalIndex++;
        }

        else if (name == "texture_height" & hasHeightMap) {
            shader.set("material.heightMaps[" + std::to_string(heightIndex) + "]", i);
            heightIndex++;
        }

    
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    shader.set("model", transformMat);  // Set model matrix
    shader.set("hasNormalMap", hasNormalMap ? 1 : 0);
    shader.set("hasSpecularMap", hasSpecularMap ? 1 : 0);
    shader.set("hasHeightMap", hasHeightMap ? 1 : 0);


    glActiveTexture(GL_TEXTURE0);

    // Draw mesh
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, (int)indices.size(), GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

Mesh::Mesh(std::vector<Vertex> vertices,
           std::vector<unsigned int> indices,
           std::vector<Texture> textures) {
    this->vertices = std::move(vertices);
    this->indices  = std::move(indices);
    this->textures = std::move(textures);

    setupMesh();
}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof (Vertex),
                 &vertices[0],
                 GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
                 indices.size() * sizeof(unsigned int) ,
                 &indices[0],
                 GL_STATIC_DRAW);

    // Vertex positions
    glEnableVertexAttribArray(VERTEX_POSITION_INDEX);
    glVertexAttribPointer(VERTEX_POSITION_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), nullptr);
    // Vertex normals
    glEnableVertexAttribArray(VERTEX_NORMAL_INDEX);
    glVertexAttribPointer(VERTEX_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*)(offsetof(Vertex, Normal)));
    // Vertex texture coordinates
    glEnableVertexAttribArray(VERTEX_TEX_COORD_INDEX);
    glVertexAttribPointer(VERTEX_TEX_COORD_INDEX, 2, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) (offsetof(Vertex, TexCoords)));
    // Vertex tangent
    glEnableVertexAttribArray(VERTEX_TANGENT_INDEX);
    glVertexAttribPointer(VERTEX_TANGENT_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) (offsetof(Vertex, Tangent)));
    // Vertex bi-tangent
    glEnableVertexAttribArray(VERTEX_BITANGENT_INDEX);
    glVertexAttribPointer(VERTEX_BITANGENT_INDEX, 3, GL_FLOAT, GL_FALSE, sizeof (Vertex), (void*) (offsetof(Vertex, Bitangent)));

    glBindVertexArray(0);
}
