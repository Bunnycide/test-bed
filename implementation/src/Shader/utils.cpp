//
// Created by a00874817 on 19/06/2024.
//

#include "Shader/utils.h"

const char* getShaderSourceText(const char* shaderName){
    std::string shader_path = getAssetPath(
            shaderName, SHADER_PATH);
    Log::debug("Reading shader from %s",shader_path.c_str());
    const char* data = readFromFile(shader_path.c_str());
    return data;
}

GLuint loadShader(GLenum type, const char* shaderSrc){
    GLuint shader = 0;
    shader = glCreateShader(type);

    if(shader == 0){
        Log::error("Failed to create a shader ID");
    }

    glShaderSource(shader, 1, &shaderSrc, nullptr);
    glCompileShader(shader);

    // Check compile status
    int compiled = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

    if( ! compiled){
        GLint infoLen = 0;
        char* infoLog = (char*)std::malloc(sizeof (char) * infoLen);
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
        glGetShaderInfoLog(shader, infoLen, nullptr, infoLog);
        Log::error("Error compiling shader:\n%s\n", infoLog);

        Log::error("Shader source\n%s\n", shaderSrc);

        std::free(infoLog);
    }

    Log::info("Shader compiled successfully\n");
    return shader;
}

GLuint compileAndLinkProgram(std::vector<GLuint> shaderIDs){
    // Create a program
    GLuint program = glCreateProgram();

    if( program == 0 ) {
        Log::error("Failed allocate shader program");
        return 0;
    }

    for(auto shaderID : shaderIDs){
        glAttachShader(program, shaderID);
    }

    // Link the program
    GLint linked = 0;
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &linked);

    if (!linked){
        GLint infoLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
        if(infoLen > 1){
            char* infoLog = (char*)std::malloc(sizeof (char) * infoLen);
            glGetProgramInfoLog(program, infoLen, nullptr, infoLog);

            Log::error("Error linking program\n%s\n", infoLog);
            std::free(infoLog);
        }

        glDeleteProgram(program);
        return 0;
    }

    Log::info("Shaders linked successfully\n");
    return program;
}