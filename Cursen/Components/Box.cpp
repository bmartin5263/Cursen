//
// Created by Brandon Martin on 3/17/19.
//

#include <Drawing/CursesManager.h>
#include "Box.h"

Box::Box(const Vect2i &pos, const Vect2i &dim) :
        Component(pos, dim)
{
    if (dim.x < 2 || dim.y < 2) throw std::logic_error("Box requires dimensions > 1");
    initialize();
}

void Box::initialize() {
    setBorder();
    this->color = Color::WHITE;
    this->draw_color = Color::WHITE;
}

void Box::render() {
    Vect2i dimensions = content.getDimensions();
    content.clear();

    // Render Top and Bottom Line
    chtype top[dimensions.x];
    chtype bottom[dimensions.x];
    top[0] = upperLeft;
    bottom[0] = lowerLeft;
    for (int i = 1; i < dimensions.x - 1; i++) {
        top[i] = upper;
        bottom[i] = lower;
    }
    top[dimensions.x - 1] = upperRight;
    bottom[dimensions.x - 1] = lowerRight;
    content.writeLine(top, Vect2i(0,0));
    for (int i = 1; i < dimensions.y - 1; i++) {
        chtype row[dimensions.x];
        row[0] = left;
        row[dimensions.x - 1] = right;
        for (int j = 1; j < dimensions.x - 1; j++) {
            row[j] = fill;
        }
        content.writeLine(row, Vect2i(0,i));
    }
    content.writeLine(bottom, Vect2i(0,dimensions.y - 1));
}

void Box::setBorder(chtype ul, chtype top, chtype ur, chtype left, chtype fill, chtype right, chtype ll, chtype bottom,
                    chtype lr)
{
    this->upperLeft = ul;
    this->upper = top;
    this->upperRight = ur;
    this->left = left;
    this->fill = fill;
    this->right = right;
    this->lowerLeft = ll;
    this->lower = bottom;
    this->lowerRight = lr;
    invalidate();
}

void Box::setColor(const Color &color) {
    setBorder();
    this->upperLeft = upperLeft | color;
    this->upper = upper | color;
    this->upperRight = upperRight | color;
    this->left = left | color;
    this->fill = fill | color;
    this->right = right | color;
    this->lowerLeft = lowerLeft | color;
    this->lower = lower | color;
    this->lowerRight = lowerRight | color;
    invalidate();
}