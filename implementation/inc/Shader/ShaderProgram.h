#ifndef OGL_MODEL_LOADER_SHADERPROGRAM_H
#define OGL_MODEL_LOADER_SHADERPROGRAM_H
#define GLM_ENABLE_EXPERIMENTAL

#include <vector>
#include <map>
#include "glad/glad.h"
#include "glm/glm.hpp"
#include <string>
#include <unordered_map>

class ShaderProgram{
private:
    std::vector<GLuint> shaderIDs;
    std::unordered_map<std::string, GLenum> uniformTypes;
    void queryActiveUniforms();
public:
    ShaderProgram()= default;
    void addShader(const char* shaderName, GLenum m_type);
    void setUniform1i(int value, const char* name);
    void compile();

    GLint getUniformLocation(const std::string &name) const;
    void use() const;
    void set(const std::string &name, float value) const;
    void set(const std::string &name, const glm::vec2 &value) const;
    void set(const std::string &name, const glm::vec3 &value) const;
    void set(const std::string &name, const glm::vec4 &value) const;
    void set(const std::string &name, const glm::mat2 &mat) const;
    void set(const std::string &name, const glm::mat3 &mat) const;
    void set(const std::string &name, const glm::mat4 &mat) const;
    void set(const std::string &name, const glm::mat2x3 &mat) const;
    void set(const std::string &name, const glm::mat3x2 &mat) const;
    void set(const std::string &name, const glm::mat2x4 &mat) const;
    void set(const std::string &name, const glm::mat4x2 &mat) const;
    void set(const std::string &name, const glm::mat3x4 &mat) const;
    void set(const std::string &name, const glm::mat4x3 &mat) const;

    void set(const std::string &name, int value) const;
    void set(const std::string &name, const glm::ivec2 &value) const;
    void set(const std::string &name, const glm::ivec3 &value) const;
    void set(const std::string &name, const glm::ivec4 &value) const;

    void set(const std::string &name, unsigned int value) const;
    void set(const std::string &name, const glm::uvec2 &value) const;
    void set(const std::string &name, const glm::uvec3 &value) const;
    void set(const std::string &name, const glm::uvec4 &value) const;

    void setMat4(std::string name, glm::mat4 mat);
    GLuint ID{};
};

#endif //OGL_MODEL_LOADER_SHADERPROGRAM_H

