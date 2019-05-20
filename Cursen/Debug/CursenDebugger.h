//
// Created by Brandon Martin on 4/8/19.
//

#ifndef CURSEN_CURSENDEBUGGER_H
#define CURSEN_CURSENDEBUGGER_H


#include "InspectionPointer.h"

namespace cursen {

    class CursenDebugger {

    public:

        CursenDebugger();
        void activateInspection();
        void deactivateInspection();
        InspectionPointer *getInspectionPointer();

    private:

        InspectionPointer *inspectionPointer;

    };
}


#endif //CURSEN_CURSENDEBUGGER_H
