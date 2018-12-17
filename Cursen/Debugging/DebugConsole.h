//
// Created by Brandon Martin on 12/17/18.
//

#ifndef CURSEN_DEBUGCONSOLE_H
#define CURSEN_DEBUGCONSOLE_H


class DebugConsole {

public:



private:

    static DebugConsole* instance;

    static DebugConsole& Instance() {
        if (instance == nullptr)
            instance = new DebugConsole;
        return *instance;
    }

    DebugConsole();
    DebugConsole(const DebugConsole& other) = delete;
    DebugConsole(DebugConsole&& other) noexcept = delete;
    DebugConsole& operator = (const DebugConsole& other) = delete;
    DebugConsole& operator = (DebugConsole&& other) = delete;
    ~DebugConsole();

};


#endif //CURSEN_DEBUGCONSOLE_H
