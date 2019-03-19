//
// Created by Brandon Martin on 3/17/19.
//

#ifndef CURSEN_BOX_H
#define CURSEN_BOX_H


#include "Component.h"

using namespace cursen;

class Box : public Component {

public:

    Box(const Vect2i& pos, const Vect2i& dim);

    void setBorder(chtype ul = ACS_ULCORNER, chtype top = ACS_HLINE, chtype ur = ACS_URCORNER,
                    chtype left = ACS_VLINE, chtype fill = ' ', chtype right = ACS_VLINE,
                    chtype ll = ACS_LLCORNER, chtype bottom = ACS_HLINE, chtype lr = ACS_LRCORNER);

    void initialize() override;
    void render() override;

    void setColor(const Color& color);

private:

    Color draw_color;
    Color color;
    chtype upperLeft;
    chtype upper;
    chtype upperRight;
    chtype left;
    chtype fill;
    chtype right;
    chtype lowerLeft;
    chtype lower;
    chtype lowerRight;

};


#endif //CURSEN_BOX_H
