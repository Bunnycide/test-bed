#include "Shader/ShaderProgram.h"
#include "Shader/utils.h"
#include "GeneralUtils/macros.h"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

void ShaderProgram::compile() {
    this->ID = compileAndLinkProgram(shaderIDs);
    queryActiveUniforms();
}

void ShaderProgram::addShader(const char *shaderName, GLenum m_type) {
    const char* shaderSrc = getShaderSourceText(shaderName);
    shaderIDs.push_back(loadShader(m_type, shaderSrc));
    std::free((void *) shaderSrc);
}

void ShaderProgram::queryActiveUniforms() {
    GLint i;
    GLint count;

    GLint size; // size of the variable
    GLenum type; // type of the variable (float, vec3 or mat4, etc.)

    const GLsizei bufSize = 256; // maximum name length
    GLchar name[bufSize]; // variable name in GLSL
    GLsizei length; // name length

    glGetProgramiv(ID, GL_ACTIVE_UNIFORMS, &count);
    Log::debug("Number of active uniforms is %d", count);
    for(i =0; i < count; i++){
        glGetActiveUniform(ID, i, sizeof(name), &length, &size, &type, name);
        uniformTypes[reinterpret_cast<GLchar*>(name)] = (GLenum)type;
    }
}

GLint ShaderProgram::getUniformLocation(const std::string &name) const {
    auto it = uniformTypes.find(name);
    if (it != uniformTypes.end()) {
        return glGetUniformLocation(ID, name.c_str());
    } else {
        std::cerr << "Uniform " << name << " not found!" << std::endl;
        return -1;
    }
}

// Set methods for float types
void ShaderProgram::set(const std::string &name, float value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform1f(location, value);
    }
}

void ShaderProgram::set(const std::string &name, const glm::vec2 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform2f(location, value.x, value.y);
    }
}

void ShaderProgram::set(const std::string &name, const glm::vec3 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform3f(location, value.x, value.y, value.z);
    }
}

void ShaderProgram::set(const std::string &name, const glm::vec4 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform4f(location, value.x, value.y, value.z, value.w);
    }
}

// Set methods for int types
void ShaderProgram::set(const std::string &name, int value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform1i(location, value);
    }
}

void ShaderProgram::set(const std::string &name, const glm::ivec2 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform2i(location, value.x, value.y);
    }
}

void ShaderProgram::set(const std::string &name, const glm::ivec3 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform3i(location, value.x, value.y, value.z);
    }
}

void ShaderProgram::set(const std::string &name, const glm::ivec4 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform4i(location, value.x, value.y, value.z, value.w);
    }
}

// Set methods for unsigned int types
void ShaderProgram::set(const std::string &name, unsigned int value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform1ui(location, value);
    }
}

void ShaderProgram::set(const std::string &name, const glm::uvec2 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform2ui(location, value.x, value.y);
    }
}

void ShaderProgram::set(const std::string &name, const glm::uvec3 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform3ui(location, value.x, value.y, value.z);
    }
}

void ShaderProgram::set(const std::string &name, const glm::uvec4 &value) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniform4ui(location, value.x, value.y, value.z, value.w);
    }
}

// Set methods for matrix types
void ShaderProgram::set(const std::string &name, const glm::mat2 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat3 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat4 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat2x3 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix2x3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat3x2 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix3x2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat2x4 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix2x4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat4x2 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix4x2fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat3x4 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix3x4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::set(const std::string &name, const glm::mat4x3 &mat) const {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix4x3fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}

void ShaderProgram::use() const{
    glUseProgram(ID);
}

void ShaderProgram::setMat4(std::string name, glm::mat4 mat) {
    GLint location = getUniformLocation(name);
    if (location != -1) {
        glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(mat));
    }
}
