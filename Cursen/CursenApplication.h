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

    static void SetDefaultHighlightColor(const Color& color) { HIGHLIGHT = color; }
    static void SetDefaultDisabledColor(const Color& color) { DISABLED = color; }
    static const Color& GetDefaultDisabledColor() { return DISABLED; }
    static const Color& GetDefaultHighlightColor() { return HIGHLIGHT; }

    static void Run(Form* startForm) { Instance().privRun(startForm); };
    static void Quit() { Instance().privQuit(); }
    static Form* GetCurrentForm() { return Instance().privGetCurrentForm(); }

private:

    static Color HIGHLIGHT;
    static Color DISABLED;

    // Instance Data
    Form* currentForm;
    int rows;
    int columns;
    bool running;

    // Static Data

    // Static-Instance Methods
    void privRun(Form *startForm);
    void privQuit();
    Form* privGetCurrentForm();

    static CursenApplication* engineInstance;

    static CursenApplication& Instance() {
        if (engineInstance == nullptr)
            engineInstance = new CursenApplication;
        return *engineInstance;
    }

    CursenApplication() = default;
    CursenApplication(const CursenApplication& other) = delete;
    CursenApplication(CursenApplication&& other) noexcept = delete;
    CursenApplication& operator = (const CursenApplication& other) = delete;
    CursenApplication& operator = (CursenApplication&& other) = delete;
    ~CursenApplication();

};


#endif //CURSEN_CURSENAPPLICATION_H
