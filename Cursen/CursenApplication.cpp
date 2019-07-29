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
            alarmManager(), eventManager(), cursesManager(), inputManager(), cursorManager(), form_stack(),
            currentForm(nullptr), nextForm(nullptr), UserUpdate([](){}), UserDraw([](){}), cursenDebugger(), palette(),
            componentMap(), argc(0), argv(nullptr), close_args(nullptr), running(false), requestFormClose(false),
            requestFormOpen(false), requestFormSet(false), total_nano(0), frames(0)
    {
        initialize();
    }

    void CursenApplication::initialize()
    {
        srand((unsigned) time(nullptr));
    }

    /*
     * Main Loop of the engine
     */
    void CursenApplication::Run(Form* startupForm)
    {
        CursenApplication& instance = Instance();
        putenv(const_cast<char *>("ESCDELAY=25"));

        StopWatch watch;

        /* Start the Engine */
        instance.running = true;

        /* Very Important! Curses must be initialized BEFORE we call initialize on a Form */
        CursesManager::Initialize(startupForm->getSize());
        instance.OpenForm(startupForm);
        instance.doFormOpen();

        /* Draw the Initial Screen */
        //Draw();

        while (instance.running)
        {
            watch.tick();

            if (instance.nextForm != nullptr)
            {
                instance.doFormOpen();
            }

            Update();
            Draw();

            if (instance.requestFormClose)
            {
                instance.doFormClose();
            }

            watch.tock();

//            Instance().total_nano += watch.getMicroseconds();
//            Instance().frames++;
//
//            CursesManager::DrawStringBottomLeft(std::to_string(Instance().total_nano / Instance().frames));
//            CursesManager::Refresh();

            // Cheap Frame-rate limiter so I don't chug CPU cycles
            std::this_thread::sleep_for(std::chrono::milliseconds(17 - watch.getMilliseconds()));
        }

        Terminate();
    }

    void CursenApplication::Update()
    {
        Form* form = GetCurrentForm();
        AlarmManager::ProcessAlarms(form->getAlarmMap(), form->getStartRequests(), form->getStopRequests());
        InputManager::ProcessInput();
        EventManager::ProcessEvents(form->getEventDispatchMap());
        Instance().UserUpdate();
        CursorManager::RefreshCursors(form->getCursors());
    }

    void CursenApplication::Draw()
    {
        CursesManager::Draw(GetCurrentForm()->getComponentDrawMap());
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
        CursenApplication& instance = Instance();
        instance.requestFormOpen = true;
        instance.nextForm = form;
    }

    void CursenApplication::doFormOpen()
    {
        Instance().form_stack.push(nextForm);
        nextForm->initialize();
        nextForm->CallOnOpen();

        nextForm = nullptr;
        requestFormOpen = false;
        requestFormSet = false;
    }

    void CursenApplication::CloseForm(void* close_args)
    {
        Instance().requestFormClose = true;
        Instance().close_args = close_args;
    }

    void CursenApplication::doFormClose()
    {
        requestFormClose = false;

        std::stack<Form*>& form_stack = Instance().form_stack;
        Form* current_form = form_stack.top();

        // Do form cleanup
        current_form->CallBeforeClosing();

        // Pop the form and call the closed callback
        form_stack.pop();
        current_form->CallOnClosed(GetReturnArgument());

        // Push the form back on temporarily to do the deletion as it is the easiest way, this is because
        // the destruction of components deregister themselves from their form.
        form_stack.push(current_form);
        delete current_form;

        // Now pop it for good
        form_stack.pop();
        if (form_stack.empty())
        {
            Quit();
        }
        else
        {
            form_stack.top()->CallOnOpen();
        }
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
    }

    void CursenApplication::Deregister(TextComponent* component)
    {
        GetCurrentForm()->deregisterComponent(component);
    }

    void CursenApplication::SetDrawOrder(TextComponent* component, size_t order)
    {
        GetCurrentForm()->setComponentDrawOrder(component, order);
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

    void* CursenApplication::GetReturnArgument()
    {
        void* val_to_return = Instance().close_args;
        Instance().close_args = nullptr;
        return val_to_return;
    }

CURSEN_CLASS_END
