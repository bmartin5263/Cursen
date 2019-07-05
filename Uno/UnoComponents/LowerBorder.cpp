//
// Created by Brandon Martin on 6/30/19.
//

#include <Cursen/Drawing/CursesManager.h>
#include "LowerBorder.h"

using namespace cursen;

void LowerBorder::initialize()
{

    border.initialize();
    border.setSize(Vect2(70, 26));
    border.setUpperLeft(CursesManager::LTEE);
    border.setUpperRight(CursesManager::RTEE);
    border.setFill(Content::INVISIBLE);
    addRelative(&border);

}
