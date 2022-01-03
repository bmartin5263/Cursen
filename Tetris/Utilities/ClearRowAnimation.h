//
// Created by Brandon Martin on 10/12/19.
//

#ifndef CURSEN_CLEARROWANIMATION_H
#define CURSEN_CLEARROWANIMATION_H


#include <Cursen/Drawing/Animation.h>
#include "DropResult.h"

class Tetris;
class ClearRowAnimation
{

public:

    void run(const DropResult& result, Tetris* game, int remainingDrops, const std::function<void()>& onComplete);
    void update();

private:

    DropResult result;
    Tetris* game;
    int col_offset;
    int row_offset;
    int remainingDrops;
    cursen::AlarmHandle alarmHandle;
    std::function<void()> onComplete;

};


#endif //CURSEN_CLEARROWANIMATION_H
