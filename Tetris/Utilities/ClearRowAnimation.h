//
// Created by Brandon Martin on 10/12/19.
//

#ifndef CURSEN_CLEARROWANIMATION_H
#define CURSEN_CLEARROWANIMATION_H


#include <Cursen/Drawing/Animation.h>
#include <Tetris/GameObjects/Tetris.h>
#include "DropResult.h"

class TetrisBoard;
class ClearRowAnimation
{

public:

    ClearRowAnimation(TetrisBoard& board);

    void run(const DropResult& result, Tetris& game, int remainingDrops);
    void update();

private:

    DropResult result;
    TetrisBoard& board;
    Tetris* game;
    int col_offset;
    int row_offset;
    int remainingDrops;
    cursen::AlarmHandle alarmHandle;

};


#endif //CURSEN_CLEARROWANIMATION_H
