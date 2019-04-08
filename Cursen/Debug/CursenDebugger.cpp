//
// Created by Brandon Martin on 4/8/19.
//

#include "CursenDebugger.h"

CursenDebugger::CursenDebugger() :
    inspectionPointer(nullptr)
{
}


void CursenDebugger::activateInspection() {
    inspectionPointer = new InspectionPointer();
    inspectionPointer->initialize();
}

void CursenDebugger::deactivateInspection() {
    delete inspectionPointer;
    inspectionPointer = nullptr;
}

InspectionPointer *CursenDebugger::getInspectionPointer() {
    return inspectionPointer;
}