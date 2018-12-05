//
// Created by Brandon Martin on 11/21/18.
//

#include <thread>
#include <curses.h>
#include "Engine.h"
#include "SceneManager.h"
#include "TerminalManager.h"
#include "SFML/Window.hpp"
#include "UITools.h"
#include "CursenObject.h"

Engine* Engine::engineInstance = nullptr;

/*
 * Main Loop of the engine
 */
void Engine::Run() {

    srand((unsigned)time(0));

    TerminalManager::Initialize();
    Instance().UserInitialization();

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        Instance().clock.processTime();
        SceneManager::ProcessOneFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    Instance().Terminate();

}

/*
 * Current location for custom user initialization
 */
void Engine::UserInitialization() {
    UITools::AddColor("white", 15, COLOR_BLACK);
    UITools::AddColor("blue", 39, COLOR_BLACK);
    UITools::AddColor("red", 199, COLOR_BLACK);
    UITools::AddColor("green", 82, COLOR_BLACK);
    UITools::AddColor("yellow", 226, COLOR_BLACK);
    UITools::AddColor("gray", 8, COLOR_BLACK);
    SceneManager::SetStartScene(new Scene);
}

void Engine::Terminate() {

    TerminalManager::Terminate();

    delete engineInstance;
    engineInstance = nullptr;
}

Engine::~Engine() {
    printf("[Engine] Deconstructed\n");
}