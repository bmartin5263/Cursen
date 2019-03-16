//
// Created by Brandon Martin on 2/21/19.
//

#ifndef CURSEN_CURSENAPPLICATION_H
#define CURSEN_CURSENAPPLICATION_H


class Form;

class CursenApplication {

public:

    static void Run(Form* startForm) { Instance().privRun(startForm); };
    static void Quit() { Instance().privQuit(); }

private:

    // Instance Data
    int rows;
    int columns;
    bool running;

    // Static Data

    // Static-Instance Methods
    void privRun(Form *startForm);
    void privQuit();

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
