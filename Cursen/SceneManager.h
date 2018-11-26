//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_SCENEMANAGER_H
#define CURSEN_SCENEMANAGER_H

#include "Scene.h"

class SceneManager {

public:

    static void ProcessOneFrame() { Instance().privProcessOneFrame(); };
    static Scene* GetCurrentScene() { return Instance().currentScene; };

private:

    void privProcessOneFrame();

    Scene* currentScene;
    Scene* nextScene;

    static SceneManager* manager;

    static SceneManager& Instance() {
        if (manager == nullptr)
            manager = new SceneManager;
        return *manager;
    }

    SceneManager();
    SceneManager(const SceneManager& other) = delete;
    SceneManager(SceneManager&& other) noexcept = delete;
    SceneManager& operator = (const SceneManager& other) = delete;
    SceneManager& operator = (SceneManager&& other) = delete;
    ~SceneManager();

};


#endif //CURSEN_SCENEMANAGER_H
