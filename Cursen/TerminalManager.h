//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_TERMINALMANAGER_H
#define CURSEN_TERMINALMANAGER_H

#include <string>

class Canvas;

class TerminalManager {

    const static int WIN_COLS = 33;
    const static int WIN_ROWS = 70;

public:

    static void ClearScreen() { Instance().privClearScreen(); };
    static void RefreshScreen() { Instance().privRefreshScreen(); }
    static void Initialize() { Instance().privInitialize(); };
    static void Terminate();

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
