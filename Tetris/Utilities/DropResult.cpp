//
// Created by Brandon Martin on 10/8/19.
//

#include "DropResult.h"

DropResult::DropResult() :
    didLose(false), nextPiece(false)
{
    rowsToClear[0] = -1;
    rowsToClear[1] = -1;
    rowsToClear[2] = -1;
    rowsToClear[3] = -1;
}
