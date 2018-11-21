//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_TERMINALMANAGER_H
#define CURSEN_TERMINALMANAGER_H

#include <string>
#include "Canvas.h"

class Canvas;

class TerminalManager {

public:

    static Canvas& GetCanvas() { return Instance().privGetCanvas(); };
    static void Initialize() { Instance().privInitialize(); };
    static void Terminate();

private:

    Canvas* mainCanvas;

    Canvas& privGetCanvas();
    void privInitialize();
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
