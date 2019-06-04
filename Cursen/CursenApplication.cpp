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
            currentForm(nullptr), running(false), argc(0), argv(nullptr)
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

        /* Start the Engine */
        Instance().running = true;

        /* Very Important! Curses must be initialized BEFORE we call initialize on a Form */
        CursesManager::Initialize(startupForm->getSize());
        Instance().OpenForm(startupForm);

        /* Draw the Initial Screen */
        Draw();

        while (Instance().running)
        {
            watch.tick();

            Update();
            Draw();

            watch.tock();

            //Instance().total_nano += watch.getMicroseconds();
            //Instance().frames++;

            // Cheap Frame-rate limiter so I don't chug CPU cycles
            std::this_thread::sleep_for(std::chrono::milliseconds(17 - watch.getMilliseconds()));
        }

        CursesManager::Terminate();

        Terminate();
    }

    void CursenApplication::Update()
    {
        AlarmManager::ProcessAlarms();
        InputManager::ProcessInput();
        EventManager::ProcessEvents();
        Instance().UserUpdate();
        CursorManager::RefreshCursors();
    }

    void CursenApplication::Draw()
    {
        CursesManager::Draw(getComponentMap());
        Instance().UserDraw();
        CursesManager::Refresh();
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

    void CursenApplication::SetCommandLineArgs(int argc, char** argv)
    {
        Instance().argc = argc;
        Instance().argv = argv;
    }

    int CursenApplication::GetArgc()
    {
        return Instance().argc;
    }

    char** CursenApplication::GetArgv()
    {
        return Instance().argv;
    }

    void CursenApplication::Register(TextComponent* component)
    {
        ComponentMap& componentMap = getComponentMap();
        auto it = componentMap[component->drawOrder].find(component);
        if (it == componentMap[component->drawOrder].end())
        {
            componentMap[component->drawOrder].insert(component);
        }
    }

    void CursenApplication::Deregister(TextComponent* component)
    {
        ComponentMap& componentMap = getComponentMap();
        auto it = componentMap[component->drawOrder].find(component);
        if (it != componentMap[component->drawOrder].end())
        {
            componentMap[component->drawOrder].erase(component);
        }
    }

    void CursenApplication::SetDrawOrder(TextComponent* component, int order)
    {
        ComponentMap& componentMap = getComponentMap();
        componentMap[component->getDrawOrder()].erase(component);
        componentMap[order].insert(component);
    }

    AlarmManager& CursenApplication::GetAlarmManager()
    {
        return Instance().alarmManager;
    }
}
