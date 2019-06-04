//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_CURSENAPPLICATION_H
#define CURSEN_CURSENAPPLICATION_H

#include <map>
#include <set>

#include "Debug/CursenDebugger.h"
#include "Drawing/ColorPalette.h"
#include "Components/TextComponent.h"
#include "Cursen/Events/AlarmManager.h"
#include "Cursen/Events/InputManager.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Cursen/Events/EventManager.h"
#include "Cursen/Cursor/CursorManager.h"

#define CURSEN_CLASS_START namespace cursen {
#define CURSEN_CLASS_END }

CURSEN_CLASS_START

    class Form;
    class InspectionPointer;

    typedef std::function<void()> UserFunction;
    typedef std::map<int, std::set<TextComponent*> > ComponentMap;

    class CursenApplication {

    public:

        static void SetCommandLineArgs(int argc, char** argv);
        static int GetArgc();
        static char** GetArgv();

        static void SetColorPalette(const ColorPalette& palette);
        static ColorPalette& GetColorPalette();

        /**
         * @brief Starts the main loop of the CursenApplication.
         *
         * @param startForm First Form to be loaded
         */
        static void Run(Form* startForm);

        /**
         * @brief Signals Cursen to terminate after the completion of the current loop.
         */
        static void Quit();

        inline static void Update();
        inline static void Draw();

        static void OpenForm(Form* form);
        static Form* GetCurrentForm();

        /**
         * @brief Sets a callback function to be called after processing events.
         *
         * @param user_callback Callback function
         */
        static void OnUpdate(UserFunction user_callback);

        /**
         * @brief Sets a callback function to be called after drawing the components
         *
         * Cursen will call this callback after it finishes drawing all of it's components
         * but before it refreshes the screen.
         *
         * @param user_callback Callback function
         */
        static void OnDraw(UserFunction user_callback);

        static CursenDebugger& GetDebugger();

        static ComponentMap& getComponentMap() { return Instance().componentMap; };

        static void Register(TextComponent* component);
        static void Deregister(TextComponent* component);
        static void SetDrawOrder(TextComponent* component, int order);

        static AlarmManager& GetAlarmManager();
        static EventManager& GetEventManager();
        static CursesManager& GetCursesManager();
        static InputManager& GetInputManager();
        static CursorManager& GetCursorManager();

    private:

        AlarmManager alarmManager;
        EventManager eventManager;
        CursesManager cursesManager;
        InputManager inputManager;
        CursorManager cursorManager;

        // Instance Data
        Form* currentForm;
        UserFunction UserUpdate;            /// User callback for after Updates
        UserFunction UserDraw;              /// User callback for after Draws
        CursenDebugger cursenDebugger;
        ColorPalette palette;
        ComponentMap componentMap;
        int argc;
        char** argv;
        bool running;

        unsigned long long int total_nano;
        unsigned long long int frames;

        // Static Data
        static void Terminate();

        // Instance Methods
        void initialize();

        //static CursenApplication* instance;

        static CursenApplication& Instance() {
            static CursenApplication instance;
            return instance;
        }

    private:
        CursenApplication();
        CursenApplication(const CursenApplication& other) = delete;
        CursenApplication(CursenApplication&& other) noexcept = delete;
        CursenApplication& operator = (const CursenApplication& other) = delete;
        CursenApplication& operator = (CursenApplication&& other) = delete;
        ~CursenApplication();

    };

CURSEN_CLASS_END


#endif //CURSEN_CURSENAPPLICATION_H
