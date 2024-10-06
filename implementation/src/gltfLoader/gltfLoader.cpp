#include "gltfLoader/gltfLoader.h"

#include <iostream>

asset loadGltf(const std::string& filePath){
    std::ifstream file(filePath);

    if(! file.is_open()){
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    json gltf;
    file >> gltf;

    asset l_asset{};

    loadAsset(gltf["asset"],l_asset);

    return l_asset;
}

void loadAsset(json& j_asset, asset& l_asset)
{
    const auto str_version = static_cast<std::string>(j_asset["version"]);
    void* temp = static_cast<char*>(std::malloc(str_version.size()));

    std::memcpy(temp, str_version.c_str(), str_version.size());
    l_asset.gltf_version = static_cast<char*>(temp);
}

