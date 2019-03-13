//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_CURSOR_H
#define CURSEN_CURSOR_H

#include "ArrowMap.h"
#include "Component.h"
#include <unordered_map>

/**
 * Cursor is a specialized component for creating a virtual cursor.
 */
class Cursor : public Component {

public:

    Cursor();
    Cursor(Component* start);

    // Override
    void setEnabled(bool value) override;

    void addComponent(Component* component, cursen::ArrowMap arrowMap);
    void removeComponent(Component* component);

    void Initialize() override;
    void Destroy() override;

private:

    void moveCursor(const Event &event);
    void click(const Event &event);

    Component* currentComponent;
    std::unordered_map<Component*, cursen::ArrowMap> componentMap;

};

#endif //CURSEN_CURSOR_H
