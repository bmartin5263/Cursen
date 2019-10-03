//
// Created by Brandon Martin on 9/29/19.
//

#include "NullUpdateStrategy.h"

bool NullUpdateStrategy::update(Tetris& tetris)
{
    (void)tetris;
    return false;
}

void NullUpdateStrategy::reset()
{

}
