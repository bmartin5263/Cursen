//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_CURSESMANAGER_H
#define CURSEN_CURSESMANAGER_H


class CursesManager {

public:

    enum Keys {
        KEY_ESCAPE = 27,
        KEY_ENTER = 10,
        KEY_BACKSPACE = 127,
    };

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
