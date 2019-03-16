//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include "CursenApplication.h"
#include "Events/EventManager.h"
#include "Drawing/CursesManager.h"


CursenApplication* CursenApplication::engineInstance = nullptr;

/*
 * Main Loop of the engine
 */
void CursenApplication::run(Form* form) {
    running = true;

    srand((unsigned)time(0));

    CursesManager::Initialize();

    form->initialize();
    CursesManager::ProcessDrawEvents();

    while (running) {
        Event e = EventManager::PollEvent();
        EventManager::ProcessEvent(e);
        CursesManager::ProcessDrawEvents();
    }

    CursesManager::Terminate();

}

void CursenApplication::quit() {
    running = false;
}

CursenApplication::~CursenApplication() {
}
