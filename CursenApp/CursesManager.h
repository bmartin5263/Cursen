//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_CURSESMANAGER_H
#define CURSEN_CURSESMANAGER_H

#include <ncurses.h>

class CursesManager {

public:

    static const int ESCAPE = 27;
    static const int ENTER = 10;
    static const int BACKSPACE = 127;
    static const int UP = KEY_UP;
    static const int DOWN = KEY_DOWN;
    static const int LEFT = KEY_LEFT;
    static const int RIGHT = KEY_RIGHT;

    static void Initialize() { Instance().initializeCurses(); };
    static void Terminate() { Instance().terminateCurses(); };

    static void PutCharacter(int c) { instance->putCharacter(c); }
    static int GetCharacter() { return instance->getCharacter(); };

    static void Beep() { instance->doBeep(); }
    static void Flash() { instance->doFlash(); }

private:

    // Instance Data
    int inputTimeout;

    // Methods
    void initializeCurses();
    void terminateCurses();

    // Static to Instance Methods
    int getCharacter();
    void putCharacter(int c);
    void doBeep();
    void doFlash();

    // Static Data

    static CursesManager* instance;

    static CursesManager& Instance() {
        if (instance == nullptr)
            instance = new CursesManager;
        return *instance;
    }

    CursesManager();
    CursesManager(const CursesManager& other) = delete;
    CursesManager(CursesManager&& other) noexcept = delete;
    CursesManager& operator = (const CursesManager& other) = delete;
    CursesManager& operator = (CursesManager&& other) = delete;
    ~CursesManager();

};



#endif //CURSEN_CURSESMANAGER_H
