//
// Created by Brandon Martin on 11/21/18.
//

#include <SFML/Window.hpp>
#include "EngineClock.h"

EngineClock::EngineClock()
{
    clock.restart();
    totalFrameTime = 0;
    previousFrameTime = 0;
}

float EngineClock::computeFrameTime()
{
    return clock.getElapsedTime().asSeconds();
}

void EngineClock::processTime()
{
    previousFrameTime = totalFrameTime;
    totalFrameTime += computeFrameTime();

    clock.restart();

    frameTime = totalFrameTime - previousFrameTime;
}
