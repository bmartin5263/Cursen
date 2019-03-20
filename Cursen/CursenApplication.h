//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_CURSENAPPLICATION_H
#define CURSEN_CURSENAPPLICATION_H

#include "Drawing/Color.h"

using namespace cursen;

class Form;

class CursenApplication {

public:

    static void SetHighlightColor(const Color &color) { HIGHLIGHT = color; }
    static void SetDisabledColor(const Color &color) { DISABLED = color; }
    static void SetBackgroundColor(const Color &color) { BACKGROUND = color; }
    static void SetDefaultColor(const Color &color) { DEFAULT_COLOR = color; }
    static const Color& GetDisabledColor() { return DISABLED; }
    static const Color& GetHighlightColor() { return HIGHLIGHT; }
    static const Color& GetBackgroundColor() { return BACKGROUND; }
    static const Color& GetDefaultColor() { return DEFAULT_COLOR; }

    static void Run(Form* startForm) { Instance().privRun(startForm); };
    static void Quit() { Instance().privQuit(); }
    static Form* GetCurrentForm() { return Instance().privGetCurrentForm(); }

private:

    static Color HIGHLIGHT;
    static Color DISABLED;
    static Color BACKGROUND;
    static Color DEFAULT_COLOR;

    // Instance Data
    Form* currentForm;
    bool running;

    // Static Data

    // Static-Instance Methods
    void privInitialize();
    void privRun(Form *startForm);
    void privQuit();
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
