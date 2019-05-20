//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include "Events/AlarmManager.h"
#include "Events/InputManager.h"
#include "CursenApplication.h"
#include "Events/EventManager.h"
#include "Drawing/CursesManager.h"
#include "Components/Form.h"

namespace cursen {

    CursenApplication *CursenApplication::engineInstance = nullptr;

    CursenApplication::CursenApplication() :
            currentForm(nullptr), running(false)
    {
        privInitialize();
    }

    void CursenApplication::privInitialize()
    {

    }

    /*
     * Main Loop of the engine
     */
    void CursenApplication::main(Form *form)
    {
        running = true;
        currentForm = form;

        srand((unsigned) time(0));

        CursesManager::Initialize(currentForm->getSize());
        currentForm->initialize();
        CursesManager::Draw();

        while (running) {
            AlarmManager::ProcessAlarms();
            InputManager::ProcessInput();
            EventManager::ProcessEvents();
            CursesManager::Draw();
        }

        CursesManager::Terminate();

    }

    void CursenApplication::privQuit()
    {
        running = false;
    }

    Form *CursenApplication::privGetCurrentForm()
    {
        return this->currentForm;
    }

    void CursenApplication::privSetColorPalette(const ColorPalette &palette)
    {
        this->palette = palette;
    }

    ColorPalette &CursenApplication::privGetColorPalette()
    {
        return this->palette;
    }

    CursenDebugger &CursenApplication::privGetDebugger()
    {
        return cursenDebugger;
    }

    CursenApplication::~CursenApplication()
    {

    }

}
