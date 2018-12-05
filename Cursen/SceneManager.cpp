//
// Created by Brandon Martin on 11/21/18.
//

#include <ncurses.h>
#include <UserInterface/UITools.h>
#include "SceneManager.h"
#include "Scene.h"

SceneManager* SceneManager::manager = nullptr;

SceneManager::SceneManager() {
    currentScene = new Scene;
    nextScene = nullptr;
}

void SceneManager::privProcessOneFrame() {
    if (nextScene != nullptr) {
        if (currentScene != nullptr) {
            currentScene->finalize();
            delete currentScene;
        }
        currentScene = nextScene;
        currentScene->initialize();
        nextScene = nullptr;
    }
    currentScene->processFrame();
}

void SceneManager::privSetStartScene(Scene* scene)
{
    currentScene = nullptr;
    nextScene = scene;
}

SceneManager::~SceneManager() {
    printf("[Scene Manager] Deconstructed\n");
}