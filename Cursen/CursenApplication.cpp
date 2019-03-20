//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include "CursenApplication.h"
#include "Events/EventManager.h"
#include "Drawing/CursesManager.h"
#include "Components/Form.h"


CursenApplication* CursenApplication::engineInstance = nullptr;

CursenApplication::CursenApplication() :
    currentForm(nullptr), running(false)
{
    privInitialize();
}

void CursenApplication::privInitialize() {

}

/*
 * Main Loop of the engine
 */
void CursenApplication::privRun(Form *form) {
    running = true;
    currentForm = form;

    srand((unsigned)time(0));

    CursesManager::Initialize();

    currentForm->initialize();
    CursesManager::Draw();

    while (running) {
        Event e = EventManager::PollEvent();
        EventManager::ProcessEvent(e);
        CursesManager::Draw();
    }

    CursesManager::Terminate();

}

void CursenApplication::privQuit() {
    running = false;
}

CursenApplication::~CursenApplication() {
}

Form* CursenApplication::privGetCurrentForm() {
    return this->currentForm;
}

void CursenApplication::privSetColorPalette(const ColorPalette &palette) {
    this->palette = palette;
}

ColorPalette &CursenApplication::privGetColorPalette() {
    return this->palette;
}
