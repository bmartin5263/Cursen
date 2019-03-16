//
// Created by Brandon Martin on 11/21/18.
//

#ifndef CURSEN_ENGINECLOCK_H
#define CURSEN_ENGINECLOCK_H

#include "SFML/System/Clock.hpp"

class EngineClock {

public:

    EngineClock();
    EngineClock(const EngineClock& other) = delete;
    EngineClock& operator = (const EngineClock& other) = delete;
    ~EngineClock() = default;

    void processTime();
    float getTotalTime() { return totalFrameTime; };;
    float getFrameTime() { return frameTime; };

private:

    float computeFrameTime();

    sf::Clock clock;
    float totalFrameTime;
    float previousFrameTime;
    float frameTime;

};


#endif //CURSEN_ENGINECLOCK_H
