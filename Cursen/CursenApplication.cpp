//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include <Cursen/Tools/StopWatch.h>
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
        user_function = [](){};
        after_draw_function = [](){};
    }

    void CursenApplication::privInitialize()
    {

    }

    /*
     * Main Loop of the engine
     */
    void CursenApplication::main(Form *form)
    {
        StopWatch watch;

        running = true;
        currentForm = form;

        srand((unsigned) time(0));

        CursesManager::Initialize(currentForm->getSize());
        currentForm->initialize();
        CursesManager::Draw();
        CursesManager::Refresh();
        while (running)
        {
            watch.tick();

            AlarmManager::ProcessAlarms();
            InputManager::ProcessInput();
            EventManager::ProcessEvents();
            user_function();
            CursesManager::Draw();
            after_draw_function();
            CursesManager::Refresh();

            watch.tock();

            std::this_thread::sleep_for(std::chrono::nanoseconds(8000000 - watch.getNanoseconds()));
        }

        CursesManager::Terminate();
        delete currentForm;

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

    void CursenApplication::OnUpdate(UserFunction user_callback)
    {
        Instance().user_function = user_callback;
    }

    void CursenApplication::OnDraw(UserFunction user_callback)
    {
        Instance().after_draw_function = user_callback;
    }

}
