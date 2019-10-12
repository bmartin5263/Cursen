//
// Created by Brandon Martin on 9/29/19.
//

#include "UpdateTimerStrategy.h"

int UpdateTimerStrategy::update(Tetris& tetris)
{
    int drops = 0;
    Duration elapsed_seconds = SystemClock::now() - last_update;
    if (elapsed_seconds.count() >= 1.0) {
        drops = (int)(elapsed_seconds.count() / 1.0);
    }
    return drops;
}

UpdateTimerStrategy::UpdateTimerStrategy() :
    last_update(SystemClock::now())
{
}

void UpdateTimerStrategy::reset()
{
    last_update = SystemClock::now();
}
