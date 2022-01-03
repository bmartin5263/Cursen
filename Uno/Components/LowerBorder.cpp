//
// Created by Brandon Martin on 6/30/19.
//

#include <Cursen/Drawing/TerminalManager.h>
#include "LowerBorder.h"

using namespace cursen;

void LowerBorder::initialize()
{

    border.initialize();
    border.setSize(Vect2(70, 26));
    border.setUpperLeft(TerminalManager::LTEE);
    border.setUpperRight(TerminalManager::RTEE);
    border.setFill(Content::TRANSPARENT);
    addRelative(border);

}
