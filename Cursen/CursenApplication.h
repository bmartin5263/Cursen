//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_CURSENAPPLICATION_H
#define CURSEN_CURSENAPPLICATION_H

#include "Drawing/ColorPalette.h"

using namespace cursen;

class Form;

class CursenApplication {

public:

    static void SetColorPalette(const ColorPalette& palette) { Instance().privSetColorPalette(palette); }
    static ColorPalette& GetColorPalette() { return Instance().privGetColorPalette(); }

    static void Run(Form* startForm) { Instance().privRun(startForm); };
    static void Quit() { Instance().privQuit(); }
    static Form* GetCurrentForm() { return Instance().privGetCurrentForm(); }

private:

    // Instance Data
    Form* currentForm;
    ColorPalette palette;
    bool running;

    // Static Data

    // Static-Instance Methods
    void privInitialize();
    void privRun(Form *startForm);
    void privQuit();

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


#endif //CURSEN_CURSENAPPLICATION_H
