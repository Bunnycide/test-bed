#ifndef OGL_MODEL_LOADER_TEXTURE2D_UTIL_H
#define OGL_MODEL_LOADER_TEXTURE2D_UTIL_H

#include "glad/glad.h"

typedef struct {
    int width, height, nrChannels;
    unsigned int textureId;
} ImageData;

ImageData loadTexture(std::string filePath);



#endif //OGL_MODEL_LOADER_TEXTURE2D_UTIL_H