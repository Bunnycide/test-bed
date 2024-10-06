//
// Created by a00874817 on 23/06/2024.
//

#include "Model/Model.h"
#include "Log/Log.h"
#include <filesystem>
#include "stb_image.h"
#include "Model/utils.h"
#include "glm/gtx/transform.hpp"


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma)
{
    std::string filename = std::string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

void Model::Draw(ShaderProgram& shaderProgram) {
    setLightingData(shaderProgram);
    for(auto & mesh : meshes){
        mesh.draw(shaderProgram);
    }
}

void Model::setDirectionalLight(glm::vec3 direction, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    directionalLight.direction = direction;
    directionalLight.ambient = ambient;
    directionalLight.diffuse = diffuse;
    directionalLight.specular = specular;
}

void Model::addPointLight(glm::vec3 position, float constant, float linear, float quadratic, glm::vec3 ambient,
    glm::vec3 diffuse, glm::vec3 specular)
{
    PointLight pointLight{};
    pointLight.position = position;
    pointLight.constant = constant;
    pointLight.linear = linear;
    pointLight.quadratic = quadratic;
    pointLight.ambient = ambient;
    pointLight.diffuse = diffuse;
    pointLight.specular = specular;
    pointLights.push_back(pointLight);
}

void Model::addSpotLight(glm::vec3 position, glm::vec3 direction, float cutOff, float outerCutOff, float constant,
    float linear, float quadratic, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular)
{
    SpotLight spotLight{};
    spotLight.position = position;
    spotLight.direction = direction;
    spotLight.cutOff = cutOff;
    spotLight.outerCutOff = outerCutOff;
    spotLight.constant = constant;
    spotLight.linear = linear;
    spotLight.quadratic = quadratic;
    spotLight.ambient = ambient;
    spotLight.diffuse = diffuse;
    spotLight.specular = specular;
    spotLights.push_back(spotLight);
}

void Model::setLightingData(ShaderProgram& shader) {
    shader.use();  // Ensure the shader is in use

    // Set directional light data
    shader.set("dirLight.direction", directionalLight.direction);
    shader.set("dirLight.ambient", directionalLight.ambient);
    shader.set("dirLight.diffuse", directionalLight.diffuse);
    shader.set("dirLight.specular", directionalLight.specular);

    // Set point lights data (assuming max 4 lights)
    for (size_t i = 0; i < pointLights.size() && i < 4; ++i) {
        std::string prefix = "pointLights[" + std::to_string(i) + "].";
        shader.set(prefix + "position", pointLights[i].position);
        shader.set(prefix + "constant", pointLights[i].constant);
        shader.set(prefix + "linear", pointLights[i].linear);
        shader.set(prefix + "quadratic", pointLights[i].quadratic);
        shader.set(prefix + "ambient", pointLights[i].ambient);
        shader.set(prefix + "diffuse", pointLights[i].diffuse);
        shader.set(prefix + "specular", pointLights[i].specular);
    }

    // Set spot lights data (assuming max 4 lights)
    for (size_t i = 0; i < spotLights.size() && i < 4; ++i) {
        std::string prefix = "spotLights[" + std::to_string(i) + "].";
        shader.set(prefix + "position", spotLights[i].position);
        shader.set(prefix + "direction", spotLights[i].direction);
        shader.set(prefix + "cutOff", spotLights[i].cutOff);
        shader.set(prefix + "outerCutOff", spotLights[i].outerCutOff);
        shader.set(prefix + "constant", spotLights[i].constant);
        shader.set(prefix + "linear", spotLights[i].linear);
        shader.set(prefix + "quadratic", spotLights[i].quadratic);
        shader.set(prefix + "ambient", spotLights[i].ambient);
        shader.set(prefix + "diffuse", spotLights[i].diffuse);
        shader.set(prefix + "specular", spotLights[i].specular);
    }
}

Model::Model(const char *path) {
    loadModel(path);
}

std::vector<Texture>
Model::loadMaterialTexture(aiMaterial *mat,  aiTextureType type, std::string typeName) {
    std::vector<Texture> textures;

    for(auto i = 0; i < mat->GetTextureCount(type); i++){

        aiString str;
        mat->GetTexture(type, i, &str);

        bool skip = false;

        for(auto & j : textures_loaded)
        {
            if(std::strcmp(j.path.data(), str.C_Str()) == 0)
            {
                textures.push_back(j);
                skip = true;
                break;
            }
        }
        if(! skip){
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), directory);
            texture.type = typeName;
            Log::debug("Texture type is %s", typeName.c_str());
            texture.path = str.C_Str();
            Log::debug("Texture path is %s", texture.path.c_str());
            textures.push_back(texture);
            textures_loaded.push_back(texture);
        }
    }

    return textures;
}

void Model::loadModel(std::string path) {
    // read file via ASSIMP | aiProcess_FlipUVs
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate  | aiProcess_CalcTangentSpace | aiProcess_FlipUVs | aiProcess_PreTransformVertices);
    // check for errors
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
    {
        std::cout << "ERROR::ASSIMP:: " << importer.GetErrorString() << std::endl;
        return;
    }
    // retrieve the directory path of the filepath
    std::filesystem::path filePath (path);
    directory = filePath.remove_filename().string();

    // process ASSIMP's root node recursively
    processNode(scene->mRootNode, scene);
    processLights(scene);
}

Mesh Model::processMesh(aiMesh *mesh, const aiScene *scene) {
    // data to fill
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.Position = vector;
        // normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.Normal = vector;
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.TexCoords = vec;
        }
        else
            vertex.TexCoords = glm::vec2(0.0f, 0.0f);
        // tangent
        vector.x = mesh->mTangents[i].x;
        vector.y = mesh->mTangents[i].y;
        vector.z = mesh->mTangents[i].z;
        vertex.Tangent = vector;
        // bitangent
        vector.x = mesh->mBitangents[i].x;
        vector.y = mesh->mBitangents[i].y;
        vector.z = mesh->mBitangents[i].z;
        vertex.Bitangent = vector;
        vertices.push_back(vertex);
    }
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        if(face.mNumIndices < 3)
        {
            continue;
        }
        assert(face.mNumIndices == 3);
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

    // 1. diffuse maps
    std::vector<Texture> diffuseMaps = loadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
    textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
    // 2. specular maps
    std::vector<Texture> specularMaps = loadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
    textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    // 3. normal maps
    std::vector<Texture> normalMaps = loadMaterialTexture(material, aiTextureType_HEIGHT, "texture_normal");
    textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
    // 4. height maps
    std::vector<Texture> heightMaps = loadMaterialTexture(material, aiTextureType_AMBIENT, "texture_height");
    textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

    // return a mesh object created from the extracted mesh data
    Mesh meshObj(vertices, indices, textures);
    meshObj.hasSpecularMap  = ! specularMaps.empty();
    meshObj.hasNormalMap    = ! normalMaps.empty();
    meshObj.hasHeightMap    = ! heightMaps.empty();

    meshObj.transformMat = aiMatrix4x4ToGlm(scene->mRootNode->mTransformation);

    return meshObj;
}

void Model::processLights(const aiScene* scene)
{
    bool isDirset = false;
    for(unsigned int i = 0; i < scene->mNumLights; i++)
    {
        aiLight* light = scene->mLights[i];

        switch (light->mType)
        {
        case aiLightSource_DIRECTIONAL:
            {
                setDirectionalLight(
                    glm::vec3(light->mDirection.x, light->mDirection.y, light->mDirection.z),// direction
                    glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b),// ambient
                    glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b),// diffuse
                    glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b) // specular
                    );
            }
            break;
        case aiLightSource_POINT:
            {
                addPointLight(
                glm::vec3(light->mPosition.x, light->mPosition.y, light->mPosition.z), //position
                1.0f,// constant
                0.09f,// linear
                0.032f,// quadratic
                glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b),// ambient
                glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b),// diffuse
                glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b) // specular
                );

            }
            break;
        case aiLightSource_SPOT:
            {

                addSpotLight(
                glm::vec3(light->mPosition.x, light->mPosition.y, light->mPosition.z),
                glm::vec3(light->mDirection.x, light->mDirection.y, light->mDirection.z),
                glm::cos(glm::radians(light->mAngleInnerCone)),
                glm::cos(glm::radians(light->mAngleOuterCone)),
                1.0f,
                0.09f,
                0.032f,
                glm::vec3(light->mColorAmbient.r, light->mColorAmbient.g, light->mColorAmbient.b),
                glm::vec3(light->mColorDiffuse.r, light->mColorDiffuse.g, light->mColorDiffuse.b),
                glm::vec3(light->mColorSpecular.r, light->mColorSpecular.g, light->mColorSpecular.b)
                );
            }
            break;
        default:
                break;
        }
    }

    if(! isDirset)
    {
        setDirectionalLight(
            glm::vec3(0.7, 0.6, 1.0),
            glm::vec3(0.2f, 0.5f, 0.7f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(1.0f, 1.0f, 1.0f)
            );
    }
}

void Model::processNode(aiNode *node, const aiScene *scene) {
// process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(processMesh(mesh, scene));
    }
    // after we've processed all the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene);
    }

}

void Model::translate(glm::vec3 position) {
    for(auto& mesh : meshes){
        mesh.transformMat = glm::translate(mesh.transformMat, position);
    }
}

void Model::rotate(float degrees, glm::vec3 axis) {
    for(auto& mesh : meshes){
        mesh.transformMat = glm::rotate(mesh.transformMat, glm::radians(degrees), axis);
    }
}

void Model::scale(glm::vec3 scale) {
    for(auto& mesh : meshes){
        mesh.transformMat = glm::scale(mesh.transformMat, scale);
    }
}
