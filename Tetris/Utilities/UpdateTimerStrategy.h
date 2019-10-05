//
// Created by Brandon Martin on 9/29/19.
//

#ifndef CURSEN_UPDATETIMERSTRATEGY_H
#define CURSEN_UPDATETIMERSTRATEGY_H


#include <chrono>
#include "UpdateStrategy.h"

class UpdateTimerStrategy : public UpdateStrategy
{
public:

    UpdateTimerStrategy();
    void reset() override;
    bool update(Tetris& tetris) override;

private:

    typedef std::chrono::system_clock SystemClock;
    typedef SystemClock::time_point TimePoint;
    typedef std::chrono::duration<double> Duration;

    TimePoint last_update;

};


#endif //CURSEN_UPDATETIMERSTRATEGY_H
