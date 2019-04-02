//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_VECT2D_H
#define CURSEN_VECT2D_H

namespace cursen {

    struct Size {

        Size() :
                x(0), y(0)
        {
        }

        Size(int x, int y) :
                x(x), y(y)
        {
        }

        Size(const Size& other) :
                x(other.x), y(other.y)
        {
        }

        Size& operator = (const Size& other) {
            this->x = other.x;
            this->y = other.y;
            return *this;
        }

        Size relativeTo(const Size& other) {
            return Size(x+other.x, y+other.y);
        }

        int x;
        int y;

    };

}

#endif //CURSEN_VECT2D_H
