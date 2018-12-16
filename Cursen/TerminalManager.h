//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_TERMINALMANAGER_H
#define CURSEN_TERMINALMANAGER_H

#include <string>
#include <UserInterface/Sprites/CursenSprite.h>

class Canvas;

class TerminalManager {

    const static int WIN_COLS = 70;
    const static int WIN_ROWS = 33;

public:

    static void ClearScreen() { Instance().privClearScreen(); };
    static void RefreshScreen() { Instance().privRefreshScreen(); }
    static void Initialize() { Instance().privInitialize(); };
    static void Terminate();
    static void Resize(int rows, int columns);
    static int GetColumns() { return WIN_COLS; };
    static int GetRows() { return WIN_ROWS; };
    static void Draw(const CursesSprite& sprite);

private:

    void privInitialize();
    void privClearScreen();
    void privRefreshScreen();

    void initializeCurses();

    static TerminalManager* managerInstance;

    static TerminalManager& Instance() {
        if (managerInstance == nullptr)
            managerInstance = new TerminalManager;
        return *managerInstance;
    }

    TerminalManager();
    TerminalManager(const TerminalManager& other) = delete;
    TerminalManager(TerminalManager&& other) noexcept = delete;
    TerminalManager& operator = (const TerminalManager& other) = delete;
    TerminalManager& operator = (TerminalManager&& other) = delete;
    ~TerminalManager();

};

#endif //CURSEN_TERMINALMANAGER_H
