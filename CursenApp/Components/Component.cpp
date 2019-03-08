//
// Created by Brandon Martin on 3/8/19.
//

#include "Events/EventManager.h"
#include "Component.h"

void Component::onKeyPress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::KeyPressed);
    f_keyPress = f;
}

void Component::onEscapePress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::EscPressed);
    f_escapePress = f;
}

void Component::onEnterPress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::EnterPressed);
    f_enterPress = f;
}

void Component::onSocketMessage(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::SocketMessage);
    f_socketMessage = f;
}

void Component::onSocketConnect(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::SocketConnected);
    f_socketConnect = f;
}

void Component::onSocketDisconnect(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::SocketDisconnected);
    f_socketDisconnect = f;
}

void Component::onDeletePress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::DeletePressed);
    f_deletePress = f;
}

void Component::onArrowPress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, Event::ArrowPressed);
    f_arrowPress = f;
}
