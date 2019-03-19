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

void Cursor::addComponent(Component* component, cursen::ArrowMap arrowMap) {
    componentMap[component] = arrowMap;
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
    Component* originalComponent = currentComponent;
    cursen::ArrowMap map = componentMap[currentComponent];
    if (event.arrowPress.right) {
        currentComponent = map.right;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return;
        }
    }
    else if (event.arrowPress.left) {
        currentComponent = map.left;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return;
        }
    }
    else if (event.arrowPress.up) {
        currentComponent = map.up;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return;
        }
    }
    else if (event.arrowPress.down) {
        currentComponent = map.down;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return;
        }
    }
    originalComponent->CallOffCursor();
    currentComponent->CallOnCursor();
}


void Cursor::removeComponent(Component *component) {
    if (componentMap.find(component) != componentMap.end()) {
        componentMap.erase(component);
        if (component == currentComponent) {

        }
    }
}

void Cursor::initialize() {

}

