//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_CURSOR_H
#define CURSEN_CURSOR_H

#include "ArrowMap.h"
#include "Components/Component.h"
#include "Components/TextComponent.h"
#include <unordered_map>

/**
 * Cursor is a specialized component for creating a virtual cursor.
 */
class Cursor : public TextComponent {

public:

    Cursor();
    Cursor(Component* start);

    // Override
    void setEnabled(bool value) override;
    void moveTo(Component *start);

    void mapComponent(Component *component, cursen::ArrowMap arrowMap);
    void unmapComponent(Component *component);

    void cursorDown();
    void cursorLeft();
    void cursorRight();
    void cursorUp();

    void initialize() override;

    void render() override {};  // no rendering
    void refresh();

private:

    void moveCursor(const Event &event);
    void enterClick(const Event &event);
    void keyClick(const Event &event);

    Component* currentComponent;
    std::unordered_map<Component*, cursen::ArrowMap> componentMap;

};

#endif //CURSEN_CURSOR_H
