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
    disabled = new Color(Color::GRAY);
    highlight = new Color(Color::YELLOW);
    background = new Color(Color::BLACK);
    default_color = new Color(Color::WHITE);
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

void CursenApplication::privSetHighlight(const Color &color) {
    delete highlight;
    this->highlight = new Color(color);
}

void CursenApplication::privSetDisabled(const Color &color) {
    delete disabled;
    this->disabled = new Color(color);
}

void CursenApplication::privSetBackground(const Color &color) {
    delete background;
    this->background = new Color(color);
}

void CursenApplication::privSetDefaultColor(const Color &color) {
    delete default_color;
    this->default_color = new Color(color);
}

Color CursenApplication::privGetHighlight() {
    return *highlight;
}

Color CursenApplication::privGetDisabled() {
    return *disabled;
}

Color CursenApplication::privGetBackground() {
    return *background;
}

Color CursenApplication::privGetDefaultColor() {
    return *default_color;
}
