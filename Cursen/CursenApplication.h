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

    class CursenApplication {

    public:

        static void SetColorPalette(const ColorPalette& palette) { Instance().privSetColorPalette(palette); }
        static ColorPalette& GetColorPalette() { return Instance().privGetColorPalette(); }

        static void Run(Form* startForm) { Instance().main(startForm); };
        static void Quit() { Instance().privQuit(); }
        static Form* GetCurrentForm() { return Instance().privGetCurrentForm(); }

        static CursenDebugger& GetDebugger() { return Instance().privGetDebugger(); };

    private:

        // Instance Data
        Form* currentForm;
        CursenDebugger cursenDebugger;
        ColorPalette palette;
        bool running;

        // Static Data

        // Static-Instance Methods
        void privInitialize();
        void main(Form *startForm);
        void privQuit();
        CursenDebugger& privGetDebugger();

        void privSetColorPalette(const ColorPalette& palette);
        ColorPalette& privGetColorPalette();
        Form* privGetCurrentForm();

        static CursenApplication* engineInstance;

        static CursenApplication& Instance() {
            if (engineInstance == nullptr)
                engineInstance = new CursenApplication;
            return *engineInstance;
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
