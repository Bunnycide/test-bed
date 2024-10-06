//
// Created by a00874817 on 25/06/2024.
//
#include <string>
#include "Texture/util.h"
#include "stb_image.h"
#include "Log/Log.h"

ImageData loadTexture(std::string filePath){
    ImageData imageData;

    glGenTextures(1, &imageData.textureId);
    glBindTexture(GL_TEXTURE_2D, imageData.textureId);
    // Set texture parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture

    unsigned char* data = stbi_load(filePath.c_str(),
                                    &imageData.width,
                                    &imageData.height,
                                    &imageData.nrChannels,
                                    0);
    if(! data){
        Log::error("Failed to load texture %s", filePath.c_str());
        return {0, 0,0, 0};
    }

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RGB,
                 imageData.width,
                 imageData.height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}