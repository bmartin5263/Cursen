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

    static Canvas& GetCanvas() { return Instance().privGetCanvas(); };
    static void Initialize() { Instance().privInitialize(); };
    static void Terminate();

private:

    Canvas* mainCanvas;

    Canvas& privGetCanvas();
    void privInitialize();

    void initializeCurses();
    void initializeCanvas();

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
