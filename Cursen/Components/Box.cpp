//
// Created by Brandon Martin on 3/17/19.
//

#include <Drawing/CursesManager.h>
#include "Box.h"

Box::Box(const Vect2i &pos, const Vect2i &dim) :
        ColorComponent(pos, dim)
{
    if (dim.x < 2 || dim.y < 2) throw std::logic_error("Box requires dimensions > 1");
    initialize();
}

void Box::initialize() {
    ColorComponent::initialize();
    setBorder();
}

void Box::render() {
    Vect2i dimensions = content.getDimensions();
    content.clear();

    // Render Top and Bottom Line
    chtype top[dimensions.x];
    chtype bottom[dimensions.x];
    top[0] = upperLeft | draw_color;
    bottom[0] = lowerLeft | draw_color;
    for (int i = 1; i < dimensions.x - 1; i++) {
        top[i] = upper | draw_color;
        bottom[i] = lower | draw_color;
    }
    top[dimensions.x - 1] = upperRight | draw_color;
    bottom[dimensions.x - 1] = lowerRight | draw_color;
    content.writeLine(top, Vect2i(0,0));
    for (int i = 1; i < dimensions.y - 1; i++) {
        chtype row[dimensions.x];
        row[0] = left | draw_color;
        row[dimensions.x - 1] = right | draw_color;
        for (int j = 1; j < dimensions.x - 1; j++) {
            row[j] = fill | draw_color;
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