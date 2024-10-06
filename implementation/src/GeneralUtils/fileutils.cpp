//
// Created by a00874817 on 19/06/2024.
//
#include "GeneralUtils/fileutils.h"

namespace fs = std::filesystem;

std::string getAssetPath(const char* resourceName, const char* folderName){
    fs::path assets_dir(ASSET_PATH);
    fs::path folder_name (folderName);
    fs::path asset_file_name (resourceName);

    fs::path asset_full_path =  assets_dir / folder_name / asset_file_name;

    return asset_full_path.generic_string();
}

const char* readFromFile(const char* absolutePath){

    std::ifstream inputFile(absolutePath);

    if (!inputFile.is_open()) {
        Log::error("Could not open the file %s ", absolutePath);
        return nullptr; // Return nullptr
    }

    std::ostringstream ss;
    ss << inputFile.rdbuf();
    size_t fileSize = ss.str().size();

    // Get the string value of the buffer
    std::string fileString = ss.str();
    // Allocate the return variable
    char* fileData = (char*)std::malloc(fileString.size() + 1);
    // Allocate a tempPtr for the copy op
    const char* tempPtr = fileString.data();
    // Copy over from temp-ptr
    std::memcpy((void*)fileData, tempPtr, fileSize);

    fileData[fileString.size()] = 0x00;

    return fileData;
}