//
// Created by Brandon Martin on 9/29/19.
//

#ifndef CURSEN_UPDATESTRATEGY_H
#define CURSEN_UPDATESTRATEGY_H


#include <Tetris/GameObjects/Tetris.h>

class UpdateStrategy
{
public:

    virtual bool update(Tetris& tetris) = 0;
    virtual void reset() = 0;

};


#endif //CURSEN_UPDATESTRATEGY_H
