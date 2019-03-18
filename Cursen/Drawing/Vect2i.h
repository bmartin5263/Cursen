//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VECT2D_H
#define CURSEN_VECT2D_H

namespace cursen {

    struct Vect2i {

        Vect2i() :
                x(0), y(0)
        {
        }

        Vect2i(int x, int y) :
                x(x), y(y)
        {
        }

        Vect2i(const Vect2i& other) :
                x(other.x), y(other.y)
        {
        }

        Vect2i& operator = (const Vect2i& other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        int x;
        int y;

    };

}

#endif //CURSEN_VECT2D_H
