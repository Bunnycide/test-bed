#ifndef OGL_MODEL_LOADER_SHADERUTILS_H
#define OGL_MODEL_LOADER_SHADERUTILS_H

#include <filesystem>
#include <vector>

#include "GeneralUtils/fileutils.h"
#include "GeneralUtils/AssetPath.h"
#include "Log/Log.h"
#include "glad/glad.h"

const char* getShaderSourceText(const char* shaderName);
GLuint loadShader(GLenum type, const char* shaderSrc);
GLuint compileAndLinkProgram(std::vector<GLuint> shaderIDs);

#endif //OGL_MODEL_LOADER_SHADERUTILS_H