//
// Created by Brandon Martin on 12/15/18.
//

#include <fstream>
#include <sstream>
#include <vector>
#include <cassert>
#include <UI/Sprites/SpriteFileParser.h>
#include "ResourceManager.h"

ResourceManager* ResourceManager::managerInstance = nullptr;

ResourceManager::ResourceManager()
{
}

void ResourceManager::LoadAllResources() {
    LoadSpriteFile("Hello");
}

void ResourceManager::LoadSpriteFile(const char *filePath) {
    std::ifstream file(filePath);
    SpriteFileParser parser(&file);
    parser.parse();

    std::string line;
    char sigil;
    while (std::getline(file, line)) {

        if (line.length() > 0) {

        } else {

        }

        std::istringstream textToSplit(line);
        std::vector<std::string> split((std::istream_iterator<std::string>(textToSplit)),
                                       std::istream_iterator<std::string>());
        if (split.size() == 0) continue;

        assert(split.size() >= 2);
        std::string key = split[0];
        std::string value = split[1];

        // make lower case
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
        std::transform(key.begin(), key.end(), key.begin(), ::tolower);
    }
}