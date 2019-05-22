//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_CURSENAPPLICATION_H
#define CURSEN_CURSENAPPLICATION_H

#include "Debug/CursenDebugger.h"
#include "Drawing/ColorPalette.h"

namespace cursen {

    class Form;
    class InspectionPointer;

    typedef std::function<void()> UserFunction;

    class CursenApplication {

    public:


        static void SetColorPalette(const ColorPalette& palette);
        static ColorPalette& GetColorPalette();

        static void Run(Form* startForm);
        static void Quit();

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
         * @param user_callback Callback function
         */
        static void OnDraw(UserFunction user_callback);

        static CursenDebugger& GetDebugger();

    private:

        // Instance Data
        Form* currentForm;
        UserFunction UserUpdate;
        UserFunction UserDraw;
        CursenDebugger cursenDebugger;
        ColorPalette palette;
        bool running;

        // Static Data
        static void Terminate();

        // Instance Methods
        void initialize();

        static CursenApplication* instance;

        static CursenApplication& Instance() {
            if (instance == nullptr)
                instance = new CursenApplication;
            return *instance;
        }

    private:
        CursenApplication();
        CursenApplication(const CursenApplication& other) = delete;
        CursenApplication(CursenApplication&& other) noexcept = delete;
        CursenApplication& operator = (const CursenApplication& other) = delete;
        CursenApplication& operator = (CursenApplication&& other) = delete;
        ~CursenApplication();

    };

}


#endif //CURSEN_CURSENAPPLICATION_H
