//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include "Cursen/Tools/StopWatch.h"
#include "Cursen/Cursor/CursorManager.h"
#include "Events/AlarmManager.h"
#include "Events/InputManager.h"
#include "CursenApplication.h"
#include "Events/EventManager.h"
#include "Drawing/CursesManager.h"
#include "Components/Form.h"

namespace cursen {

    CursenApplication *CursenApplication::instance = nullptr;

    CursenApplication::CursenApplication() :
            currentForm(nullptr), running(false)
    {
        initialize();
    }

    void CursenApplication::initialize()
    {
        srand((unsigned) time(0));
        UserUpdate = [](){};
        UserDraw = [](){};
    }

    /*
     * Main Loop of the engine
     */
    void CursenApplication::Run(Form* startupForm)
    {
        StopWatch watch;

        Instance().running = true;

        /* Very Important! Curses must be initialized BEFORE we call initialize on a Form */
        CursesManager::Initialize(startupForm->getSize());
        Instance().OpenForm(startupForm);

        CursesManager::Draw();
        CursesManager::Refresh();
        while (Instance().running)
        {
            watch.tick();

            AlarmManager::ProcessAlarms();
            InputManager::ProcessInput();
            EventManager::ProcessEvents();
            Instance().UserUpdate();
            CursorManager::RefreshCursors();

            CursesManager::Draw();
            Instance().UserDraw();
            CursesManager::Refresh();

            watch.tock();

            // Cheap Frame-rate limiter so I don't chug CPU cycles
            std::this_thread::sleep_for(std::chrono::milliseconds(16 - watch.getMilliseconds()));
        }

        EventManager::Terminate();
        AlarmManager::Terminate();
        InputManager::Terminate();
        CursesManager::Terminate();

        Terminate();
    }

    void CursenApplication::Quit()
    {
        Instance().running = false;
    }

    void CursenApplication::SetColorPalette(const cursen::ColorPalette& palette)
    {
        Instance().palette = palette;
    }

    ColorPalette& CursenApplication::GetColorPalette()
    {
        return Instance().palette;
    }

    void CursenApplication::OpenForm(Form* form)
    {
        form->initialize();
        Instance().currentForm = form;
    }

    void CursenApplication::OnUpdate(UserFunction user_callback)
    {
        Instance().UserUpdate = user_callback;
    }

    void CursenApplication::OnDraw(UserFunction user_callback)
    {
        Instance().UserDraw = user_callback;
    }

    void CursenApplication::Terminate()
    {
        delete instance;
        instance = nullptr;
    }

    CursenDebugger& CursenApplication::GetDebugger()
    {
        return Instance().cursenDebugger;
    }

    Form* CursenApplication::GetCurrentForm()
    {
        return Instance().currentForm;
    }

    CursenApplication::~CursenApplication()
    {
        delete currentForm;
        currentForm = nullptr;
    }
}
