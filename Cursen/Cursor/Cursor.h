//
// Created by Brandon Martin on 3/8/19.
//

#ifndef CURSEN_CURSOR_H
#define CURSEN_CURSOR_H

#include <unordered_map>

#include "ArrowMap.h"
#include "Cursen/Components/StandardComponent.h"

namespace cursen {

/**
 * Cursor is a specialized component for creating a virtual cursor.
 */
    class Cursor : public Component {

    public:

        Cursor();
        Cursor(VisualComponent *start);

        void initialize() override;
        VisualComponent* getHoveredComponent();

        void setEnabled(bool value) override;
        void moveTo(VisualComponent *start);
        void mapComponent(VisualComponent *component, cursen::ArrowMap arrowMap);
        void unmapComponent(VisualComponent *component);
        bool cursorDown();
        bool cursorLeft();
        bool cursorRight();
        bool cursorUp();
        bool refresh();

    private:

        void moveCursor(const Event &event);
        void enterClick(const Event &event);
        void keyClick(const Event &event);

        VisualComponent *currentComponent;
        std::unordered_map<VisualComponent *, cursen::ArrowMap> componentMap;

    };
}

#endif //CURSEN_CURSOR_H
