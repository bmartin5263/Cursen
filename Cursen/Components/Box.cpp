//
// Created by Brandon Martin on 3/17/19.
//

#include <Drawing/CursesManager.h>
#include "Box.h"

Box::Box() :
    ColorComponent(Size(0,0), Size(2,2))
{
    //initialize();
}

Box::Box(const Size &pos, const Size &dim) :
        ColorComponent(pos, dim)
{
    if (dim.x < 2 || dim.y < 2) throw std::logic_error("Box requires dimensions > 1");
    //initialize();
}

void Box::initialize() {
    ColorComponent::initialize();
    setBorder();
}

void Box::render() {
    Size dimensions = content.getDimensions();
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
    content.writeLine(top, Size(0,0));
    for (int i = 1; i < dimensions.y - 1; i++) {
        chtype row[dimensions.x];
        row[0] = left | draw_color;
        row[dimensions.x - 1] = right | draw_color;
        for (int j = 1; j < dimensions.x - 1; j++) {
            row[j] = fill | draw_color;
        }
        content.writeLine(row, Size(0,i));
    }
    content.writeLine(bottom, Size(0,dimensions.y - 1));
}

void Box::setBorder(chtype ul, chtype top, chtype ur, chtype left, chtype fill, chtype right, chtype ll, chtype bottom,
                    chtype lr)
{
    setUpperLeft(ul);
    setUpper(top);
    setUpperRight(ur);
    setLeft(left);
    setFill(fill);
    setRight(right);
    setLowerLeft(ll);
    setLower(bottom);
    setLowerRight(lr);
}

void Box::setUpperRight(const chtype &upperRight) {
    this->upperRight = upperRight;
    invalidate();
}

void Box::setUpperLeft(const chtype &upperLeft) {
    this->upperLeft = upperLeft;
    invalidate();
}

void Box::setUpper(const chtype &upper) {
    this->upper = upper;
    invalidate();
}

void Box::setLower(const chtype &lower) {
    this->lower = lower;
    invalidate();
}

void Box::setLowerLeft(const chtype &lowerLeft) {
    this->lowerLeft = lowerLeft;
    invalidate();
}

void Box::setLowerRight(const chtype &lowerRight) {
    this->lowerRight = lowerRight;
    invalidate();
}

void Box::setLeft(const chtype &left) {
    this->left = left;
    invalidate();
}

void Box::setRight(const chtype &right) {
    this->right = right;
    invalidate();
}

void Box::setFill(const chtype &fill) {
    this->fill = fill;
    invalidate();
}