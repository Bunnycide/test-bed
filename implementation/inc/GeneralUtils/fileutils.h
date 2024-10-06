#ifndef OGL_MODEL_LOADER_FILEUTILS_H
#define OGL_MODEL_LOADER_FILEUTILS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <filesystem>
#include "Log/Log.h"
#include "AssetPath.h"

std::string getAssetPath(const char* resourceName, const char* folderName);
const char* readFromFile(const char* absolutePath);

#endif //OGL_MODEL_LOADER_FILEUTILS_H