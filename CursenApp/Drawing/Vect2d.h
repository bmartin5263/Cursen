//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VECT2D_H
#define CURSEN_VECT2D_H

namespace cursen {

    struct Vect2d {

        Vect2d() :
                x(0), y(0)
        {
        }

        Vect2d(int x, int y) :
                x(x), y(y)
        {
        }

        Vect2d(const Vect2d& other) :
                x(other.x), y(other.y)
        {
        }

        Vect2d& operator = (const Vect2d& other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        int x;
        int y;

    };

}

#endif //CURSEN_VECT2D_H
