//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_INTRECT_H
#define CURSEN_INTRECT_H

struct IntRect {

    IntRect() :
            x(0), y(0), cols(0), rows(0)
    {
    }

    IntRect(int x, int y) :
            x(x), y(y), cols(0), rows(0)
    {
    }

    IntRect(int x, int y, int cols, int rows) :
            x(x), y(y), cols(cols), rows(rows)
    {
    }

    IntRect(const IntRect& other) :
            x(other.x), y(other.y), cols(other.cols), rows(other.rows)
    {
    }

    IntRect& operator = (const IntRect& other) {
        this->x = other.x;
        this->y = other.y;
        this->cols = other.cols;
        this->rows = other.rows;
        return *this;
    }

    int x;
    int y;
    int cols;
    int rows;

};

#endif //CURSEN_INTRECT_H
