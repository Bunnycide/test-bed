//
// Created by a00874817 on 26/06/2024.
//
#include "SkyBox/util.h"

#define TEXTURE_FACE_BACK "back"
#define TEXTURE_FACE_BOTTOM "bottom"
#define TEXTURE_FACE_FRONT "front"
#define TEXTURE_FACE_LEFT "left"
#define TEXTURE_FACE_RIGHT "right"
#define TEXTURE_FACE_TOP "top"

#define EXTENSION_JPG ".jpg"
#define EXTENSION_PNG ".png"

unsigned int loadCubeMap(const char* cubeMapPath, const char* extension){
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);



    return 0;
}