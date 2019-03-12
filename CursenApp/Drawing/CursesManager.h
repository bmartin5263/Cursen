//
// Created by Brandon Martin on 3/7/19.
//

#ifndef CURSEN_CURSESMANAGER_H
#define CURSEN_CURSESMANAGER_H

#include <ncurses.h>
#include <queue>
#include <string>
#include "Drawing/DrawRequest.h"
#include "ClearRequest.h"

class CursesManager {

public:

    static const int ESCAPE = 27;
    static const int ENTER = 10;
    static const int BACKSPACE = 127;
    static const int UP = KEY_UP;
    static const int DOWN = KEY_DOWN;
    static const int LEFT = KEY_LEFT;
    static const int RIGHT = KEY_RIGHT;

    static void Initialize() { Instance().initializeCurses(); }
    static void Terminate() { Instance().terminateCurses(); }

    static void EnqueueDraw(DrawRequest request) { Instance().enqueueDraw(request); };
    static void EnqueueClear(ClearRequest request) { Instance().enqueueClear(request); };
    static DrawRequest GetDrawRequest() { return Instance().getDrawRequest(); };
    static ClearRequest GetClearRequest() { return Instance().getClearRequest(); };

    static void DrawChar(int c) { instance->putCharacter(c); }
    static void DrawString(const std::string &string) { instance->drawString(string.c_str()); }
    static void DrawString(const char *string) { instance->drawString(string); }
    static void DrawString(const std::string &string, int x, int y) { instance->drawString(string.c_str(), x, y); }
    static void DrawString(const char *string, int x, int y) { instance->drawString(string, x, y); }
    static int GetChar() { return instance->getCharacter(); }

    static void Beep() { instance->doBeep(); }
    static void Flash() { instance->doFlash(); }

    static void ProcessDrawEvents() { Instance().processDrawEvents(); };

private:

    // Instance Data
    int inputTimeout;
    std::queue<DrawRequest> drawQueue;
    std::queue<ClearRequest> clearQueue;

    // Methods
    void initializeCurses();
    void terminateCurses();

    // Static to Instance Methods
    int getCharacter();
    void putCharacter(int c);
    void drawString(const char *string);
    void drawString(const char *string, int x, int y);
    void doBeep();
    void doFlash();
    void processDrawEvents();
    DrawRequest getDrawRequest();
    void enqueueDraw(DrawRequest);
    ClearRequest getClearRequest();
    void enqueueClear(ClearRequest);

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
