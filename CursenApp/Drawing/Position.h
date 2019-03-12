//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_POSITION_H
#define CURSEN_POSITION_H


#include <Drawing/IntRect.h>

struct Position {

public:

    Position() {
    };

    Position(IntRect current) :
        current(current), next(current)
    {
    }

    Position(IntRect current, IntRect next) :
        current(current), next(next)
    {
    }

    IntRect current;
    IntRect next;

};


#endif //CURSEN_POSITION_H
