//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include "SFML/Window.hpp"
#include "CursenApplication.h"
#include "Events/EventManager.h"
#include "CursesManager.h"


CursenApplication* CursenApplication::engineInstance = nullptr;

/*
 * Main Loop of the engine
 */
void CursenApplication::run(Form* form) {
    running = true;

    srand((unsigned)time(0));

    CursesManager::Initialize();

    form->init();

    while (running) {
        Event e = EventManager::PollEvent();
        EventManager::ProcessEvent(e);
    }

    CursesManager::Terminate();

}

void CursenApplication::quit() {
    running = false;
}

CursenApplication::~CursenApplication() {
}
