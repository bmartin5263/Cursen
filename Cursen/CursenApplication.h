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

    static void SetHighlightColor(const Color &color) { Instance().privSetHighlight(color); }
    static void SetDisabledColor(const Color &color) { Instance().privSetDisabled(color); }
    static void SetBackgroundColor(const Color &color) { Instance().privSetBackground(color); }
    static void SetDefaultColor(const Color &color) { Instance().privSetDefaultColor(color); }
    static const Color GetDisabledColor() { return Instance().privGetDefaultColor(); }
    static const Color GetHighlightColor() { return Instance().privGetHighlight(); }
    static const Color GetBackgroundColor() { return Instance().privGetBackground(); }
    static const Color GetDefaultColor() { return Instance().privGetDefaultColor(); }

    static void Run(Form* startForm) { Instance().privRun(startForm); };
    static void Quit() { Instance().privQuit(); }
    static Form* GetCurrentForm() { return Instance().privGetCurrentForm(); }

private:

    // Instance Data
    Form* currentForm;
    Color* highlight;
    Color* disabled;
    Color* background;
    Color* default_color;
    bool running;

    // Static Data

    // Static-Instance Methods
    void privInitialize();
    void privRun(Form *startForm);
    void privQuit();

    void privSetHighlight(const Color& color);
    void privSetDisabled(const Color& color);
    void privSetBackground(const Color& color);
    void privSetDefaultColor(const Color& color);
    Color privGetHighlight();
    Color privGetDisabled();
    Color privGetBackground();
    Color privGetDefaultColor();
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
