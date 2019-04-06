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
}

void InspectionPointer::render() {
    getContent()->writeLine(std::to_string(POINTER), Size(0,0), TextAlignment::LEFT, Color::RED);
}