//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_SCENEMANAGER_H
#define CURSEN_SCENEMANAGER_H


class SceneManager {

public:

    static void ProcessOneFrame() { Instance().privProcessOneFrame(); };

private:

    void privProcessOneFrame();

    static SceneManager* engineInstance;

    static SceneManager& Instance() {
        if (engineInstance == nullptr)
            engineInstance = new SceneManager;
        return *engineInstance;
    }

    SceneManager() = default;
    SceneManager(const SceneManager& other) = delete;
    SceneManager(SceneManager&& other) noexcept = delete;
    SceneManager& operator = (const SceneManager& other) = delete;
    SceneManager& operator = (SceneManager&& other) = delete;
    ~SceneManager();

};


#endif //CURSEN_SCENEMANAGER_H
