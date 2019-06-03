//
// Created by Brandon Martin on 3/8/19.
//

#include <cassert>
#include <algorithm>

#include "Cursen/CursenApplication.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Cursen/Events/EventManager.h"
#include "Component.h"

namespace cursen {

    Component::Component() :
            enabled(true), invalid(true), hidden(false), silenced(false), cursable(true), registeredForUpdates(false),
            drawOrder(0) {
        id = "n/a";
    }

    Component::Component(const Vect2 &pos) :
            enabled(true), position(pos), hidden(false), invalid(true), cursable(true), registeredForUpdates(false),
            drawOrder(0) {
        id = "n/a";
    }

    void Component::add(Component *component) {
        assert(component != nullptr);
        component->setParent(this);
        component->setDrawOrder(this->drawOrder + 1);
        children.push_back(component);
    }

    void Component::addRelative(Component *component) {
        assert(component != nullptr);
        component->move(this->position);
        add(component);
    }

    void Component::remove(Component *component) {
        component->setParent(nullptr);
        children.erase(std::remove(children.begin(), children.end(), component), children.end());
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

    void Component::onDeletePress(std::function<void(const Event &)> f) {
        EventManager::Register(*this, EventType::DeletePressed);
        f_deletePress = f;
    }

    void Component::onArrowPress(std::function<void(const Event &)> f) {
        EventManager::Register(*this, EventType::ArrowPressed);
        f_arrowPress = f;
    }

    void Component::enableIf(std::function<bool()> f)
    {
        if (!registeredForUpdates) {
            EventManager::Register(*this, EventType::Update);
            registeredForUpdates = true;
        }
        f_enableIf = f;
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

    void Component::onUpdate(std::function<void()> f)
    {
        if (!registeredForUpdates) {
            EventManager::Register(*this, EventType::Update);
            registeredForUpdates = true;
        }
        f_update = f;
    }

    void Component::setEnabled(bool value) {
        this->enabled = value;
    }

    bool Component::isEnabled() const {
        return enabled;
    }

    void Component::setHidden(bool value) {
        hidden = value;
    }

    bool Component::isHidden() const {
        return hidden;
    }

    void Component::CallKeyPress(const Event &e) {
        if (!isSilenced()) {
            try {
                f_keyPress(e);
            }
            catch (std::bad_function_call) {
                // Pass
            }
        }
    }

    void Component::CallEscapePress(const Event &e) {
        if (!isSilenced()) {
            try {
                f_escapePress(e);
            }
            catch (std::bad_function_call) {
                // Pass
            }
        }
    }

    void Component::CallEnterPress(const Event &e) {
        if (!isSilenced()) {
            try {
                f_enterPress(e);
            }
            catch (std::bad_function_call) {
                // Pass
            }
        }
    }

    void Component::CallDeletePress(const Event &e) {
        if (!isSilenced()) {
            try {
                f_deletePress(e);
            }
            catch (std::bad_function_call) {
                // Pass
            }
        }
    }

    void Component::CallArrowPress(const Event &e) {
        if (!isSilenced()) {
            try {
                f_arrowPress(e);
            }
            catch (std::bad_function_call) {
                // Pass
            }
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

    std::function<bool()>& Component::GetEnableIf()
    {
        return f_enableIf;
    }

    std::function<void()>& Component::GetUpdate()
    {
        return f_update;
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

    void Component::detachOffCursor() {
        f_offCursor = 0;
    }

    void Component::detachEnableIf()
    {
        f_enableIf = 0;
    }

    void Component::detachUpdate()
    {
        f_update = 0;
    }

    void Component::move(const Vect2 &movement) {
        position += movement;
        for (auto child : children) {
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

    Vect2 Component::getPosition() const {
        return this->position;
    }

    void Component::setPosition(const Vect2 &pos) {
        this->position = pos;
        invalidate();
    }

    const std::vector<Component *> &Component::getChildren() {
        return children;
    }

    Component::~Component() {
    }

    int Component::getDrawOrder() {
        return drawOrder;
    }

    void Component::setDrawOrder(int order) {
        drawOrder = order;
    }

    void Component::setSilenced(bool value) {
        this->silenced = value;
    }

    bool Component::isSilenced() {
        return silenced;
    }

    void Component::setCursable(bool value) {
        this->cursable = value;
    }

    bool Component::isCursable() {
        return cursable;
    }


}