//
// Created by Brandon Martin on 3/8/19.
//

#include <Events/EventManager.h>
#include <Drawing/CursesManager.h>
#include "Cursor.h"

Cursor::Cursor() :
    currentComponent(nullptr)
{
}

Cursor::Cursor(Component* start) :
    currentComponent(start)
{
}

void Cursor::mapComponent(Component *component, cursen::ArrowMap arrowMap) {
    componentMap[component] = arrowMap;
    if (currentComponent == nullptr) {
        currentComponent = component;
    }
}

void Cursor::setEnabled(bool value) {
    if (currentComponent != nullptr) {
        Component::setEnabled(value);
        if (enabled) {
            onArrowPress(std::bind(&Cursor::moveCursor, this, std::placeholders::_1));
            onEnterPress(std::bind(&Cursor::enterClick, this, std::placeholders::_1));
            onKeyPress(std::bind(&Cursor::keyClick, this, std::placeholders::_1));
            currentComponent->CallOnCursor();
        }
        else {
            currentComponent->CallOffCursor();
            detachArrowPress();
            detachEnterPress();
            detachKeyPress();
        }
    }
}

void Cursor::enterClick(const Event &event) {
    currentComponent->CallOnClick();
}

void Cursor::keyClick(const Event &event) {
    if (event.key.code == ' ') {
        currentComponent->CallOnClick();
    }
}

void Cursor::moveCursor(const Event &event) {
    if (event.arrowPress.right) {
        if (!cursorRight()) {
            if (!cursorLeft()) {
                if (!cursorDown()) {
                    if (!cursorUp()) {
                        throw std::logic_error("Cursor is trapped.");
                    }
                }
            }
        }
    }
    else if (event.arrowPress.left) {
        if (!cursorLeft()) {
            if (!cursorRight()) {
                if (!cursorDown()) {
                    if (!cursorUp()) {
                        throw std::logic_error("Cursor is trapped.");
                    }
                }
            }
        }
    }
    else if (event.arrowPress.up) {
        if (!cursorUp()) {
            if (!cursorDown()) {
                if (!cursorLeft()) {
                    if (!cursorRight()) {
                        throw std::logic_error("Cursor is trapped.");
                    }
                }
            }
        }
    }
    else if (event.arrowPress.down) {
        if (!cursorDown()) {
            if (!cursorUp()) {
                if (!cursorLeft()) {
                    if (!cursorRight()) {
                        throw std::logic_error("Cursor is trapped.");
                    }
                }
            }
        }
    }
}


void Cursor::unmapComponent(Component *component) {
    if (componentMap.find(component) != componentMap.end()) {
        componentMap.erase(component);
        if (component == currentComponent) {

        }
    }
}

void Cursor::initialize() {

}

void Cursor::refresh() {
    if (currentComponent == nullptr || !currentComponent->isEnabled()) {
        cursorDown();
    }
}

void Cursor::moveTo(Component *start) {
    currentComponent = start;
}

bool Cursor::cursorDown() {
    Component* originalComponent = currentComponent;
    cursen::ArrowMap map = componentMap[currentComponent];
    currentComponent = map.down;
    if (currentComponent == nullptr) {
        currentComponent = originalComponent;
        return false;
    }
    while (!currentComponent->isEnabled()) {
        currentComponent = componentMap[currentComponent].down;
        if (currentComponent == nullptr || currentComponent == originalComponent) {
            currentComponent = originalComponent;
            return currentComponent->isEnabled();
        }
    }
    originalComponent->CallOffCursor();
    currentComponent->CallOnCursor();
    return true;
}

bool Cursor::cursorLeft() {
    Component* originalComponent = currentComponent;
    cursen::ArrowMap map = componentMap[currentComponent];
    currentComponent = map.left;
    if (currentComponent == nullptr) {
        currentComponent = originalComponent;
        return false;
    }
    while (!currentComponent->isEnabled()) {
        currentComponent = componentMap[currentComponent].left;
        if (currentComponent == nullptr || currentComponent == originalComponent) {
            currentComponent = originalComponent;
            return currentComponent->isEnabled();
        }
    }
    originalComponent->CallOffCursor();
    currentComponent->CallOnCursor();
    return true;
}

bool Cursor::cursorRight() {
    Component* originalComponent = currentComponent;
    cursen::ArrowMap map = componentMap[currentComponent];
    currentComponent = map.right;
    if (currentComponent == nullptr) {
        currentComponent = originalComponent;
        return false;
    }
    while (!currentComponent->isEnabled()) {
        currentComponent = componentMap[currentComponent].right;
        if (currentComponent == nullptr || currentComponent == originalComponent) {
            currentComponent = originalComponent;
            return currentComponent->isEnabled();
        }
    }
    originalComponent->CallOffCursor();
    currentComponent->CallOnCursor();
    return true;
}

bool Cursor::cursorUp() {
    Component* originalComponent = currentComponent;
    cursen::ArrowMap map = componentMap[currentComponent];
    currentComponent = map.up;
    if (currentComponent == nullptr) {
        currentComponent = originalComponent;
        return false;
    }
    while (!currentComponent->isEnabled()) {
        currentComponent = componentMap[currentComponent].up;
        if (currentComponent == nullptr || currentComponent == originalComponent) {
            currentComponent = originalComponent;
            return currentComponent->isEnabled();
        }
    }
    originalComponent->CallOffCursor();
    currentComponent->CallOnCursor();
    return true;
}
