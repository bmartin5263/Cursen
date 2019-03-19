//
// Created by Brandon Martin on 3/8/19.
//

#include <Drawing/DrawRequest.h>
#include <Drawing/CursesManager.h>
#include <cassert>
#include <CursenApplication.h>
#include "Events/EventManager.h"
#include "Component.h"

Component::Component() :
        enabled(true), invalid(true)
{
}

Component::Component(const Vect2i &pos) :
        enabled(true), position(pos), invalid(true)
{
}

Component::Component(const Vect2i &pos, const Vect2i &dim) :
        enabled(true), position(pos), body(TextBody(dim)), invalid(true)
{
}


Component::~Component() {

}

void Component::addComponent(Component *component) {
    assert(component != nullptr);
    component->setParent(this);
    components.push_back(component);
}

void Component::removeComponent(Component *component) {
    component->setParent(nullptr);
}

Component *Component::getParent() {
    return parent;
}

void Component::setParent(Component *component) {
    this->parent = component;
}

void Component::onKeyPress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::KeyPressed);
    f_keyPress = f;
}

void Component::onEscapePress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::EscPressed);
    f_escapePress = f;
}

void Component::onEnterPress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::EnterPressed);
    f_enterPress = f;
}

void Component::onSocketMessage(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::SocketMessage);
    f_socketMessage = f;
}

void Component::onSocketConnect(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::SocketConnected);
    f_socketConnect = f;
}

void Component::onSocketDisconnect(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::SocketDisconnected);
    f_socketDisconnect = f;
}

void Component::onDeletePress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::DeletePressed);
    f_deletePress = f;
}

void Component::onArrowPress(std::function<void(const Event &)> f) {
    EventManager::Register(*this, EventType::ArrowPressed);
    f_arrowPress = f;
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

void Component::setEnabled(bool value) {
    enabled = value;
}

bool Component::isEnabled() {
    return enabled;
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

void Component::detachKeyPress() {
    EventManager::Deregister(*this, EventType::KeyPressed);
    f_keyPress = 0;
}

void Component::detachEscapePress() {
    EventManager::Deregister(*this, EventType::EscPressed);
    f_escapePress = 0;
}

void Component::detachEnterPress() {
    EventManager::Deregister(*this, EventType::EnterPressed);
    f_enterPress = 0;
}

void Component::detachSocketMessage() {
    EventManager::Deregister(*this, EventType::SocketMessage);
    f_socketMessage = 0;
}

void Component::detachSocketConnect() {
    EventManager::Deregister(*this, EventType::SocketConnected);
    f_socketConnect = 0;
}

void Component::detachSocketDisconnect() {
    EventManager::Deregister(*this, EventType::SocketDisconnected);
    f_socketDisconnect = 0;
}

void Component::detachDeletePress() {
    EventManager::Deregister(*this, EventType::DeletePressed);
    f_deletePress = 0;
}

void Component::detachArrowPress() {
    EventManager::Deregister(*this, EventType::ArrowPressed);
    f_arrowPress = 0;
}

void Component::detachOnCursor() {
    f_onCursor = 0;
}

void Component::detachOnClick() {
    f_onClick = 0;
}

void Component::detachOffCursor(){
    EventManager::Deregister(*this, EventType::ArrowPressed);
    f_offCursor = 0;
}

void Component::move(const Vect2i& movement) {
    position.x += movement.x;
    position.y += movement.y;
    for (auto child : components) {
        child->move(movement);
    }
}

void Component::invalidate() {
    invalid = true;
}

void Component::validate() {
    invalid = false;
}

bool Component::isInvalid() {
    return invalid;
}

TextBody& Component::getTextBody() {
    return body;
}