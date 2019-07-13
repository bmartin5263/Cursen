//
// Created by Brandon Martin on 2/21/19.
//

#include <cstdlib>
#include <ctime>
#include <thread>
#include <cassert>
#include "Cursen/Tools/StopWatch.h"
#include "Cursen/Cursor/CursorManager.h"
#include "Events/AlarmManager.h"
#include "Events/InputManager.h"
#include "CursenApplication.h"
#include "Events/EventManager.h"
#include "Drawing/CursesManager.h"
#include "Components/Form.h"

CURSEN_CLASS_START

    //CursenApplication *CursenApplication::instance = nullptr;

    CursenApplication::CursenApplication() :
            currentForm(nullptr), running(false), argc(0), argv(nullptr), nextForm(nullptr), requestFormClose(false),
            requestFormOpen(false), requestFormSet(false)
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
        putenv(const_cast<char *>("ESCDELAY=25"));

        StopWatch watch;

        /* Start the Engine */
        Instance().running = true;

        /* Very Important! Curses must be initialized BEFORE we call initialize on a Form */
        CursesManager::Initialize(startupForm->getSize());
        Instance().OpenForm(startupForm);
        Instance().doFormOpen();

        /* Draw the Initial Screen */
        Draw();

        while (Instance().running)
        {
            watch.tick();

            if (Instance().nextForm != nullptr)
            {
                Instance().doFormOpen();
            }

            Update();
            Draw();

            if (Instance().requestFormClose)
            {
                Instance().doFormClose();
            }

            watch.tock();

            //Instance().total_nano += watch.getMicroseconds();
            //Instance().frames++;

            // Cheap Frame-rate limiter so I don't chug CPU cycles
            std::this_thread::sleep_for(std::chrono::milliseconds(17 - watch.getMilliseconds()));
        }

        Terminate();
    }

    void CursenApplication::Update()
    {
        Form* form = GetCurrentForm();
        AlarmManager::ProcessAlarms(form->getAlarmMap());
        InputManager::ProcessInput();
        EventManager::ProcessEvents(form->getEventDispatchMap());
        Instance().UserUpdate();
        CursorManager::RefreshCursors(form->getCursors());
    }

    void CursenApplication::Draw()
    {
        // Form.getComponentDrawMap()
        Form* form = GetCurrentForm();
        CursesManager::Draw(form->getComponentDrawMap());
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
        Instance().requestFormOpen = true;
        Instance().nextForm = form;
    }

    void CursenApplication::doFormOpen()
    {
        Instance().form_stack.push(nextForm);
        nextForm->initialize();

        nextForm = nullptr;
        requestFormOpen = false;
        requestFormSet = false;
    }

    void CursenApplication::CloseForm()
    {
        Instance().requestFormClose = true;
    }

    void CursenApplication::doFormClose()
    {
        std::stack<Form*>& form_stack = Instance().form_stack;
        Form* current_form = form_stack.top();
        delete current_form;
        form_stack.pop();
        if (form_stack.empty())
        {
            Quit();
        }
        requestFormClose = false;
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
    }

    CursenDebugger& CursenApplication::GetDebugger()
    {
        return Instance().cursenDebugger;
    }

    Form* CursenApplication::GetCurrentForm()
    {
        assert(Instance().form_stack.top() != nullptr);
        return Instance().form_stack.top();
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
        GetCurrentForm()->registerComponent(component);
        //ComponentMap& componentMap = getComponentMap();
        //auto it = componentMap[component->drawOrder].find(component);
        //if (it == componentMap[component->drawOrder].end())
        //{
        //    componentMap[component->drawOrder].insert(component);
        //}
    }

    void CursenApplication::Deregister(TextComponent* component)
    {
        GetCurrentForm()->deregisterComponent(component);
        //ComponentMap& componentMap = getComponentMap();
        //auto it = componentMap[component->drawOrder].find(component);
        //if (it != componentMap[component->drawOrder].end())
        //{
        //    componentMap[component->drawOrder].erase(component);
        //}
    }

    void CursenApplication::SetDrawOrder(TextComponent* component, int order)
    {
        GetCurrentForm()->setDrawOrder(component, order);
    }

    AlarmManager& CursenApplication::GetAlarmManager()
    {
        return Instance().alarmManager;
    }

    EventManager& CursenApplication::GetEventManager()
    {
        return Instance().eventManager;
    }

    CursesManager& CursenApplication::GetCursesManager()
    {
        return Instance().cursesManager;
    }

    InputManager& CursenApplication::GetInputManager()
    {
        return Instance().inputManager;
    }

    CursorManager& CursenApplication::GetCursorManager()
    {
        return Instance().cursorManager;
    }

    void CursenApplication::RegisterToCurrentForm(TextComponent* component)
    {
        Instance().GetCurrentForm()->registerComponent(component);
    }

    void CursenApplication::DeregisterFromCurrentForm(TextComponent* component)
    {
        Instance().GetCurrentForm()->registerComponent(component);
    }

CURSEN_CLASS_END
