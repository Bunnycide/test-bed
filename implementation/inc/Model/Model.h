//
// Created by a00874817 on 23/06/2024.
//

#ifndef OGL_MODEL_LOADER_MODEL_H
#define OGL_MODEL_LOADER_MODEL_H

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

#include "Shader/ShaderProgram.h"
#include "Mesh.h"
#include "glm/glm.hpp"

unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    Model() = default;
    explicit Model(const char* path);

    void scale(glm::vec3 scale);
    void rotate(float degrees, glm::vec3 axis);
    void translate(glm::vec3 position);

    void Draw(ShaderProgram& shaderProgram);

    // Light-related methods and attributes
    void setDirectionalLight(glm::vec3 direction,
                            glm::vec3 ambient,
                            glm::vec3 diffuse,
                            glm::vec3 specular);

    void addPointLight(glm::vec3 position,
        float constant,
        float linear,
        float quadratic,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular);

    void addSpotLight(glm::vec3 position,
        glm::vec3 direction,
        float cutOff,
        float outerCutOff,
        float constant,
        float linear,
        float quadratic,
        glm::vec3 ambient,
        glm::vec3 diffuse,
        glm::vec3 specular);

    // PBR-related methods and attributes
    void setAlbedoMap(const std::string& path);
    void setNormalMap(const std::string& path);
    void setMetallicMap(const std::string& path);
    void setRoughnessMap(const std::string& path);
    void setAOMap(const std::string& path);

private:
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);
    void processNode(aiNode* node, const aiScene *scene);
    Mesh processMesh(aiMesh* mesh, const aiScene *scene);
    void processLights(const aiScene *scene);
    void setLightingData(ShaderProgram& shader);

    std::vector<Texture> loadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);

    // Light-related attributes
    struct DirectionalLight {
        glm::vec3 direction;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    } directionalLight;

    struct PointLight {
        glm::vec3 position;
        float constant;
        float linear;
        float quadratic;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
    std::vector<PointLight> pointLights;

    struct SpotLight {
        glm::vec3 position;
        glm::vec3 direction;
        float cutOff;
        float outerCutOff;
        float constant;
        float linear;
        float quadratic;
        glm::vec3 ambient;
        glm::vec3 diffuse;
        glm::vec3 specular;
    };
    std::vector<SpotLight> spotLights;

    // PBR-related attributes
    Texture albedoMap;
    Texture normalMap;
    Texture metallicMap;
    Texture roughnessMap;
    Texture aoMap;

};

#endif //OGL_MODEL_LOADER_MODEL_H