//
// Created by Brandon Martin on 12/15/18.
//

#ifndef CURSEN_SPRITEMANAGER_H
#define CURSEN_SPRITEMANAGER_H


#include "CursenSprite.h"

class SpriteManager {

public:

    static CursenSprite GetSprite(std::string resourceKey);

private:

    std::unordered_map<std::string, CursenSprite> spriteMap;

    static SpriteManager* managerInstance;

    static SpriteManager& Instance() {
        if (managerInstance == nullptr)
            managerInstance = new SpriteManager;
        return *managerInstance;
    }

    SpriteManager() = default;
    SpriteManager(const SpriteManager& other) = delete;
    SpriteManager(SpriteManager&& other) noexcept = delete;
    SpriteManager& operator = (const SpriteManager& other) = delete;
    SpriteManager& operator = (SpriteManager&& other) = delete;
    ~SpriteManager();

};


#endif //CURSEN_SPRITEMANAGER_H
