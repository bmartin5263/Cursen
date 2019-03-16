//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_CURSOR_H
#define CURSEN_CURSOR_H

#include "ArrowMap.h"
#include "Component.h"
#include <unordered_map>

class TextComponent;

/**
 * Cursor is a specialized component for creating a virtual cursor.
 */
class Cursor : public Component {

public:

    Cursor();
    Cursor(TextComponent* start);

    // Override
    void setEnabled(bool value) override;

    void addComponent(TextComponent* component, cursen::ArrowMap arrowMap);
    void removeComponent(TextComponent* component);

    void initialize() override;
    void destroy() override;

private:

    void moveCursor(const Event &event);
    void click(const Event &event);

    TextComponent* currentComponent;
    std::unordered_map<TextComponent*, cursen::ArrowMap> componentMap;

};

#endif //CURSEN_CURSOR_H
