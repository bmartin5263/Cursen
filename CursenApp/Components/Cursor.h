//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_CURSOR_H
#define CURSEN_CURSOR_H

#include "Component.h"
#include <unordered_map>

struct ArrowMap {

    ArrowMap() {
        this->left = nullptr;
        this->up = nullptr;
        this->down = nullptr;
        this->right = nullptr;
    }

    ArrowMap(const ArrowMap& other) {
        //CursesManager::Beep();
        this->left = other.left;
        this->down = other.down;
        this->right = other.right;
        this->up = other.up;
    }

    ArrowMap& operator = (const ArrowMap& other) {
        this->left = other.left;
        this->down = other.down;
        this->right = other.right;
        this->up = other.up;

        return *this;
    }

    ArrowMap(Component* left, Component* up, Component* right, Component* down) {
        this->left = left;
        this->up = up;
        this->down = down;
        this->right = right;
    }

    Component* left;
    Component* up;
    Component* right;
    Component* down;

};

/**
 * Cursor is a specialized component for creating a virtual cursor.
 */
class Cursor : public Component {

public:

    Cursor();
    Cursor(Component* start);
    ~Cursor();

    // Override
    void setEnabled(bool value);

    void addComponent(Component* component, ArrowMap arrowMap);

private:

    void moveCursor(const Event &event);
    void click(const Event &event);

    Component* currentComponent;
    std::unordered_map<Component*, ArrowMap> componentMap;

};


#endif //CURSEN_CURSOR_H
