//
// Created by Brandon Martin on 12/17/18.
//

#include "DebugConsole.h"
#include "SFML/Time.hpp"

DebugConsole* DebugConsole::instance = nullptr;

DebugConsole::DebugConsole() :
    connected(false)
{
}

bool DebugConsole::privConnect(const char *address, const unsigned short port) {
    sf::Socket::Status status = clientSocket.connect(address, port, sf::seconds(3.0));
    if (status == sf::Socket::Status::Done) {
        connected = true;
        return true;
    } else {
        return false;
    }
}

void DebugConsole::privDisconnect() {
    clientSocket.disconnect();
    connected = false;
}

void DebugConsole::privOut(const char* message, const long& length) {
    if (connected) {
        size_t sent = 0;
        while (sent != length) {
            clientSocket.send(message, (size_t)length, sent);
        }
    }
}

void DebugConsole::Terminate() {
    delete instance;
    instance = nullptr;
}

DebugConsole::~DebugConsole() {
    if (connected) {
        Out("Goodbye!");
        privDisconnect();
    }
}