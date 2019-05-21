//
// Created by Brandon Martin on 11/21/18.
//

#include <thread>
#include <curses.h>
#include "Debug/DebugConsole.h"
#include "Engine.h"
#include "SceneManager.h"
#include "TerminalManager.h"
#include "SFML/Window.hpp"
#include "UITools.h"
#include "CursenObject.h"

#ifdef WIN32
#include <windows.h>
#elif _POSIX_C_SOURCE >= 199309L
#include <time.h>   // for nanosleep
#else
#include <unistd.h> // for usleep
#endif

void sleep_ms(int milliseconds) // cross-platform sleep function
{
#ifdef WIN32
    Sleep(milliseconds);
#elif _POSIX_C_SOURCE >= 199309L
    struct timespec ts;
    ts.tv_sec = milliseconds / 1000;
    ts.tv_nsec = (milliseconds % 1000) * 1000000;
    nanosleep(&ts, NULL);
#else
    usleep(milliseconds * 1000);
#endif
}

Engine* Engine::engineInstance = nullptr;

/*
 * Main Loop of the engine
 */
void Engine::Run() {

    srand((unsigned)time(0));

    DebugConsole::Connect();
    DebugConsole::Out("Connected!");
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

    // Terminate Console Last
    DebugConsole::Terminate();
}

Engine::~Engine() {
    DebugConsole::Out("Engine Deconstructed");
}