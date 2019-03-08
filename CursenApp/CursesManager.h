//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_CURSESMANAGER_H
#define CURSEN_CURSESMANAGER_H


class CursesManager {

public:

    enum Keys {
        KEY_ESCAPE = 27
    };

    static void Initialize() { Instance().initializeCurses(); };
    static void Terminate() { Instance().terminateCurses(); };

    static void PutCharacter(int c) { instance->putCharacter(c); }
    static int GetCharacter() { return instance->getCharacter(); };

private:

    // Instance Data
    int inputTimeout;

    // Methods
    void initializeCurses();
    void terminateCurses();

    // Static to Instance Methods
    int getCharacter();
    void putCharacter(int c);

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
