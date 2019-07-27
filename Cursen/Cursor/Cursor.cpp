//
// Created by Brandon Martin on 3/8/19.
//

#include "Cursen/Events/EventManager.h"
#include "Cursen/Drawing/CursesManager.h"
#include "Cursor.h"
#include "CursorManager.h"

namespace cursen {

    Cursor::Cursor() :
            currentComponent(nullptr) {
    }

    Cursor::Cursor(VisualComponent *start) :
            currentComponent(start) {
    }

    void Cursor::initialize()
    {
        CursorManager::Register(this);
    }

    void Cursor::mapComponent(VisualComponent *component, cursen::ArrowMap arrowMap) {
        componentMap[component] = arrowMap;
        if (currentComponent == nullptr) {
            currentComponent = component;
        }
    }

    void Cursor::setEnabled(bool value) {
        if (currentComponent != nullptr) {
            Component::setEnabled(value);
            if (isEnabled()) {
                onArrowPress([&](const Event& event) { this->moveCursor(event); } );
                onEnterPress([&](const Event& event) { this->enterClick(event); } );
                onKeyPress([&](const Event& event) { this->keyClick(event); } );
                currentComponent->CallOnCursor();
            } else {
                detachArrowPress();
                detachEnterPress();
                detachKeyPress();
                currentComponent->CallOffCursor();
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
                            //throw std::logic_error("Cursor is trapped.");
                        }
                    }
                }
            }
        } else if (event.arrowPress.left) {
            if (!cursorLeft()) {
                if (!cursorRight()) {
                    if (!cursorDown()) {
                        if (!cursorUp()) {
                            //throw std::logic_error("Cursor is trapped.");
                        }
                    }
                }
            }
        } else if (event.arrowPress.up) {
            if (!cursorUp()) {
                if (!cursorDown()) {
                    if (!cursorLeft()) {
                        if (!cursorRight()) {
                            //throw std::logic_error("Cursor is trapped.");
                        }
                    }
                }
            }
        } else if (event.arrowPress.down) {
            if (!cursorDown()) {
                if (!cursorUp()) {
                    if (!cursorLeft()) {
                        if (!cursorRight()) {
                            //throw std::logic_error("Cursor is trapped.");
                        }
                    }
                }
            }
        }
    }


    void Cursor::unmapComponent(VisualComponent *component) {
        if (componentMap.find(component) != componentMap.end()) {
            componentMap.erase(component);
            if (component == currentComponent) {

            }
        }
    }

    bool Cursor::refresh()
    {
        if (isEnabled())
        {
            if (currentComponent == nullptr || !currentComponent->isCursable())
            {
                if (!cursorDown() && !cursorUp() && !cursorLeft() && !cursorRight())
                {
                    return false;
                }
            }
        }
        return true;
    }

    void Cursor::moveTo(VisualComponent *start) {
        currentComponent = start;
    }

    bool Cursor::cursorDown() {
        VisualComponent *originalComponent = currentComponent;
        cursen::ArrowMap map = componentMap[currentComponent];
        currentComponent = map.down;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return currentComponent->isCursable();
        }
        while (!currentComponent->isCursable()) {
            currentComponent = componentMap[currentComponent].down;
            if (currentComponent == nullptr || currentComponent == originalComponent) {
                currentComponent = originalComponent;
                return currentComponent->isCursable();
            }
        }
        originalComponent->CallOffCursor();
        currentComponent->CallOnCursor();
        return true;
    }

    bool Cursor::cursorLeft() {
        VisualComponent *originalComponent = currentComponent;
        cursen::ArrowMap map = componentMap[currentComponent];
        currentComponent = map.left;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return currentComponent->isCursable();
        }
        while (!currentComponent->isCursable()) {
            currentComponent = componentMap[currentComponent].left;
            if (currentComponent == nullptr || currentComponent == originalComponent) {
                currentComponent = originalComponent;
                return currentComponent->isCursable();
            }
        }
        originalComponent->CallOffCursor();
        currentComponent->CallOnCursor();
        return true;
    }

    bool Cursor::cursorRight() {
        VisualComponent *originalComponent = currentComponent;
        cursen::ArrowMap map = componentMap[currentComponent];
        currentComponent = map.right;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return currentComponent->isCursable();
        }
        while (!currentComponent->isCursable()) {
            currentComponent = componentMap[currentComponent].right;
            if (currentComponent == nullptr || currentComponent == originalComponent) {
                currentComponent = originalComponent;
                return currentComponent->isCursable();
            }
        }
        originalComponent->CallOffCursor();
        currentComponent->CallOnCursor();
        return true;
    }

    bool Cursor::cursorUp() {
        VisualComponent *originalComponent = currentComponent;
        cursen::ArrowMap map = componentMap[currentComponent];
        currentComponent = map.up;
        if (currentComponent == nullptr) {
            currentComponent = originalComponent;
            return currentComponent->isCursable();
        }
        while (!currentComponent->isCursable()) {
            currentComponent = componentMap[currentComponent].up;
            if (currentComponent == nullptr || currentComponent == originalComponent) {
                currentComponent = originalComponent;
                return currentComponent->isCursable();
            }
        }
        originalComponent->CallOffCursor();
        currentComponent->CallOnCursor();
        return true;
    }

    VisualComponent* Cursor::getHoveredComponent()
    {
        return currentComponent;
    }
}
