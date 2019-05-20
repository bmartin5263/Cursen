//
// Created by Brandon Martin on 4/6/19.
//

#include "InspectionPointer.h"

namespace cursen {

    InspectionPointer::InspectionPointer() :
            TextComponent(Vect2(0, 0), Vect2(1, 1)) {

    }


    void InspectionPointer::initialize() {
        TextComponent::initialize();

        onArrowPress(std::bind(&InspectionPointer::movePointer, this, std::placeholders::_1));
        onKeyPress(std::bind(&InspectionPointer::pressSpace, this, std::placeholders::_1));

        invalidate();
    }

    void InspectionPointer::render() {
        getContent()->writeLine("@", Vect2(0, 0), TextAlignment::LEFT, Color::RED);
    }

    void InspectionPointer::movePointer(const Event &event) {
        if (event.arrowPress.down) {
            move(Vect2(0, 1));
            if (boxSize != Vect2(0, 0)) boxSize.y += 1;
        }
        if (event.arrowPress.up) {
            move(Vect2(0, -1));
            if (boxSize != Vect2(0, 0)) boxSize.y -= 1;
        }
        if (event.arrowPress.right) {
            move(Vect2(1, 0));
            if (boxSize != Vect2(0, 0)) boxSize.x += 1;
        }
        if (event.arrowPress.left) {
            move(Vect2(-1, 0));
            if (boxSize != Vect2(0, 0)) boxSize.x -= 1;
        }
        if (boxSize.x == 0 || boxSize.y == 0) boxSize = Vect2(0, 0);
    }

    void InspectionPointer::pressSpace(const Event &event) {
        if (boxSize == Vect2(0, 0)) {
            boxSize = Vect2(1, 1);
        } else {
            boxSize = Vect2(0, 0);
        }
        boxLoc = getPosition();
    }

    InspectionPointer::~InspectionPointer() {
        detachArrowPress();
        detachKeyPress();
    }

}