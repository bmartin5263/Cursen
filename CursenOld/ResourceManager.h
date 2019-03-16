//
// Created by Brandon Martin on 12/15/18.
//

#ifndef CURSEN_RESOURCEMANAGER_H
#define CURSEN_RESOURCEMANAGER_H


class ResourceManager {

public:

    static void LoadAllResources();
    static void LoadSpriteFile(const char* filePath);

private:

    static ResourceManager* managerInstance;

    static ResourceManager& Instance() {
        if (managerInstance == nullptr)
            managerInstance = new ResourceManager;
        return *managerInstance;
    }

    ResourceManager();
    ResourceManager(const ResourceManager& other) = delete;
    ResourceManager(ResourceManager&& other) noexcept = delete;
    ResourceManager& operator = (const ResourceManager& other) = delete;
    ResourceManager& operator = (ResourceManager&& other) = delete;
    ~ResourceManager();

};


#endif //CURSEN_RESOURCEMANAGER_H
