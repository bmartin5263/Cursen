//
// Created by Brandon Martin on 3/17/19.
//

#include "Box.h"

namespace cursen {

    Box::Box() :
            StandardComponent(Vect2(0,0), Vect2(2,2))
    {
    }

    Box::Box(const Vect2 &pos, const Vect2 &dim) :
            StandardComponent(pos, dim)
    {
    }

    void Box::initialize() {
        StandardComponent::initialize();
        setBorder();
    }

    void Box::render() {
        StandardComponent::render();
        Content& content = getContent();

        ColorPair& draw_color = getCurrentDrawColor();
        Vect2 dimensions = content.getSize();
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
        content.writeLine(top, Vect2(0,0));
        for (int i = 1; i < dimensions.y - 1; i++) {
            chtype row[dimensions.x];
            row[0] = left | draw_color;
            row[dimensions.x - 1] = right | draw_color;
            for (int j = 1; j < dimensions.x - 1; j++) {
                row[j] = fill | draw_color;
            }
            content.writeLine(row, Vect2(0,i));
        }
        content.writeLine(bottom, Vect2(0,dimensions.y - 1));
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

    void Box::setTransparentFill()
    {
        this->fill = Content::TRANSPARENT;
        invalidate();
    }

}