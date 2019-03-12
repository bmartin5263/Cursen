//
// Created by Brandon Martin on 3/8/19.
//

#include <Drawing/DrawRequest.h>
#include <Drawing/CursesManager.h>
#include "Events/EventManager.h"
#include "Component.h"

Component::Component() :
    enabled(true), body(TextBody()), position(Vect2d()), clearRequest(CursesManager::GetClearRequest())
{
    body.resize(Vect2d(1,1));
    refresh();
}

void Component::move(const Vect2d& movement) {
    position.x += movement.x;
    position.y += movement.y;
    refresh();
}


void Component::draw() {
    for (Component* c : children) {
        c->draw();
    }

}

void Component::invalidate() {
    // Request Redraw
    CursesManager::EnqueueClear(clearRequest);
    DrawRequest drawRequest = CursesManager::GetDrawRequest();
    drawRequest.setBody(&this->body);
    drawRequest.setPosition(this->position);
    CursesManager::EnqueueDraw(drawRequest);
    clearRequest = CursesManager::GetClearRequest();
    clearRequest.setPosition(position);
    clearRequest.setDimensions(body.getDimensions());
}

void Component::refresh() {
    draw();
    invalidate();
}

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

void Component::setEnabled(bool value) {
    enabled = value;
}

bool Component::isEnabled() {
    return enabled;
}

void Component::onCursor(std::function<void()> f) {
    f_onCursor = f;
}

void Component::offCursor(std::function<void()> f) {
    f_offCursor = f;
}

void Component::onClick(std::function<void()> f) {
    f_onClick = f;
}

void Component::CallKeyPress(const Event& e) {
    try {
        f_keyPress(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallEscapePress(const Event& e) {
    try {
        f_escapePress(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallEnterPress(const Event& e) {
    try {
        f_enterPress(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallSocketMessage(const Event& e) {
    try {
        f_socketMessage(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallSocketDisconnect(const Event& e) {
    try {
        f_socketDisconnect(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallSocketConnect(const Event& e) {
    try {
        f_socketConnect(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallDeletePress(const Event& e) {
    try {
        f_deletePress(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallArrowPress(const Event& e) {
    try {
        f_arrowPress(e);
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallOnCursor() {
    try {
        f_onCursor();
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallOffCursor() {
    try {
        f_offCursor();
    }
    catch (std::bad_function_call) {
        // Pass
    }
}

void Component::CallOnClick() {
    try {
        f_onClick();
    }
    catch (std::bad_function_call) {
        // Pass
    }
}
