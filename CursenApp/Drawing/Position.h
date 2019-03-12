//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_POSITION_H
#define CURSEN_POSITION_H


#include <Drawing/Vect2d.h>

struct Position {

public:

    Position() {
    };

    Position(Vect2d current) :
        current(current), next(current)
    {
    }

    Position(Vect2d current, Vect2d next) :
        current(current), next(next)
    {
    }

    Vect2d current;
    Vect2d next;

};


#endif //CURSEN_POSITION_H
