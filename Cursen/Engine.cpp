//
// Created by Brandon Martin on 11/21/18.
//

#include <thread>
#include "Engine.h"
#include "TerminalManager.h"
#include "SFML/Window.hpp"

Engine* Engine::engineInstance = nullptr;

void Engine::Run() {

    TerminalManager::Initialize();

    // Load Resources

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        //Instance().gameclock.ProcessTime();
        //SceneManager::ProcessOneFrame();
    }

    Instance().Terminate();

}

void Engine::Terminate() {

    TerminalManager::Terminate();

    delete engineInstance;
    engineInstance = nullptr;
}

Engine::~Engine() {
    printf("[Engine] Deconstructed\n");
}