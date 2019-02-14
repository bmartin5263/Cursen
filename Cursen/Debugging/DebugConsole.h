//
// Created by Brandon Martin on 12/17/18.
//

#ifndef CURSEN_DEBUGCONSOLE_H
#define CURSEN_DEBUGCONSOLE_H


#include <SFML/network.hpp>

class DebugConsole {

public:

    static void Terminate();

    static bool Connect(const char* address="127.0.0.1", const unsigned short port=(unsigned short)55001) {
        return Instance().privConnect(address, port);
    };

    static void Disconnect() {
        return Instance().privDisconnect();
    };

    static void Out(std::string& message) {
        Instance().privOut(message.c_str(), message.length()+1);
    };

    static void Out(const char* message) {
        Instance().privOut(message, strlen(message)+1);
    };

private:

    bool privConnect(const char* address, const unsigned short port);
    void privDisconnect();
    void privOut(const char* message, const long& length);

    sf::TcpSocket clientSocket;
    bool connected;

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
