#include <Texture/Texture2D.h>

Texture2D::Texture2D(const char* imageName) {
    imageData = loadTexture(getAssetPath(imageName, "textures").c_str());

    if(imageData.width == 0){}
    Log::error("Failed to load texture");
}
