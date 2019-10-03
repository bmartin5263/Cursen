//
// Created by Brandon Martin on 9/29/19.
//

#include "UpdateTimerStrategy.h"

bool UpdateTimerStrategy::update(Tetris& tetris)
{
    bool update = false;
    Duration elapsed_seconds = std::chrono::system_clock::now() - last_update;
    if (elapsed_seconds.count() >= 1.0) {
        update = true;
        tetris.drop();
    }
    return update;
}

UpdateTimerStrategy::UpdateTimerStrategy() :
    last_update(std::chrono::system_clock::now())
{
}

void UpdateTimerStrategy::reset()
{
    last_update = std::chrono::system_clock::now();
}
