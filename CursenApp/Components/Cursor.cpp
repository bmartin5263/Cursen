//
// Created by Brandon Martin on 3/8/19.
//

#include <Events/EventManager.h>
#include <Drawing/CursesManager.h>
#include "Components/TextComponent.h"
#include "Cursor.h"

Cursor::Cursor() :
    currentComponent(nullptr)
{
}

Cursor::Cursor(TextComponent* start) :
    currentComponent(start)
{
}

void Cursor::addComponent(TextComponent* component, cursen::ArrowMap arrowMap) {
    componentMap[component] = arrowMap;
}



void Cursor::setEnabled(bool value) {
    if (currentComponent != nullptr) {
        Component::setEnabled(value);
        if (enabled) {
            onArrowPress(std::bind(&Cursor::moveCursor, this, std::placeholders::_1));
            onEnterPress(std::bind(&Cursor::click, this, std::placeholders::_1));
        }
        else {
            EventManager::Deregister(*this, Event::ArrowPressed);
            EventManager::Deregister(*this, Event::EnterPressed);
        }
    }
}

void Cursor::click(const Event &event) {
    currentComponent->CallOnClick();
}

void Cursor::moveCursor(const Event &event) {
    TextComponent* originalComponent = currentComponent;
    cursen::ArrowMap map = componentMap[currentComponent];
    if (event.arrowPress.right) {
        currentComponent = map.right;
        //if (currentComponent == nullptr) {
        //    currentComponent = originalComponent;
        //    return;
        //}
    }
    else if (event.arrowPress.left) {
        currentComponent = map.left;
        //if (currentComponent == nullptr) {
        //    currentComponent = originalComponent;
        //    return;
        //}
    }
    else if (event.arrowPress.up) {
        currentComponent = map.up;
        //if (currentComponent == nullptr) {
        //    currentComponent = originalComponent;
        //    return;
        //}
    }
    else if (event.arrowPress.down) {
        currentComponent = map.down;
        //if (currentComponent == nullptr) {
        //    currentComponent = originalComponent;
        //    return;
        //}
    }
    originalComponent->CallOffCursor();
    currentComponent->CallOnCursor();
}


void Cursor::removeComponent(TextComponent *component) {
    if (componentMap.find(component) != componentMap.end()) {
        componentMap.erase(component);
        if (component == currentComponent) {

        }
    }
}

void Cursor::initialize() {

}

void Cursor::destroy() {

}
