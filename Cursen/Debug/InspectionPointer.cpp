//
// Created by Brandon Martin on 4/6/19.
//

#include "InspectionPointer.h"

InspectionPointer::InspectionPointer() :
    TextComponent(Size(0,0), Size(1,1))
{

}


void InspectionPointer::initialize() {
    TextComponent::initialize();

    onArrowPress(std::bind(&InspectionPointer::movePointer, this, std::placeholders::_1));
    onKeyPress(std::bind(&InspectionPointer::pressSpace, this, std::placeholders::_1));

    invalidate();
}

void InspectionPointer::render() {
    getContent()->writeLine("@", Size(0,0), TextAlignment::LEFT, Color::RED);
}

void InspectionPointer::movePointer(const Event &event) {
    if (event.arrowPress.down) {
        move(Size(0,1));
        if (boxSize != Size(0,0)) boxSize.y += 1;
    }
    if (event.arrowPress.up) {
        move(Size(0,-1));
        if (boxSize != Size(0,0)) boxSize.y -= 1;
    }
    if (event.arrowPress.right) {
        move(Size(1,0));
        if (boxSize != Size(0,0)) boxSize.x += 1;
    }
    if (event.arrowPress.left) {
        move(Size(-1,0));
        if (boxSize != Size(0,0)) boxSize.x -= 1;
    }
    if (boxSize.x == 0 || boxSize.y == 0) boxSize = Size(0,0);
}

void InspectionPointer::pressSpace(const Event &event) {
    if (boxSize == Size(0,0)) {
        boxSize = Size(1,1);
    }
    else {
        boxSize = Size(0,0);
    }
    boxLoc = getPosition();
}

InspectionPointer::~InspectionPointer() {
    detachArrowPress();
    detachKeyPress();
}
