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

    TerminalManager::Initialize();
    Instance().userInitialization();

    CursenObject o(true);

    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        Instance().clock.processTime();
        SceneManager::ProcessOneFrame();
    }

    Instance().Terminate();

}

/*
 * Current location for custome user initialization
 */
void Engine::userInitialization() {
    UITools::AddColor("white", 15, COLOR_BLACK);
    UITools::AddColor("blue", 39, COLOR_BLACK);
    UITools::AddColor("red", 199, COLOR_BLACK);
    UITools::AddColor("green", 82, COLOR_BLACK);
    UITools::AddColor("yellow", 226, COLOR_BLACK);
    UITools::AddColor("gray", 8, COLOR_BLACK);
}

void Engine::Terminate() {

    TerminalManager::Terminate();

    delete engineInstance;
    engineInstance = nullptr;
}

Engine::~Engine() {
    printf("[Engine] Deconstructed\n");
}