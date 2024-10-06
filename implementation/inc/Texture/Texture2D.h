#ifndef OGL_MODEL_LOADER_TEXTURE2D_H
#define OGL_MODEL_LOADER_TEXTURE2D_H

#include "GeneralUtils/fileutils.h"
#include "stb_image.h"
#include "glad/glad.h"
#include "util.h"
#include "Texture/util.h"

class Texture2D {
public:
    ImageData imageData{};
    Texture2D() = default;
    explicit Texture2D(const char* imageName);

};

#endif //OGL_MODEL_LOADER_TEXTURE2D_H