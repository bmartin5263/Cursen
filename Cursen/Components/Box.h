//
// Created by Brandon Martin on 3/17/19.
//

#ifndef CURSEN_BOX_H
#define CURSEN_BOX_H

#include "StandardComponent.h"

namespace cursen {

    class Box : public StandardComponent {

    public:

        Box();
        Box(const Vect2& pos, const Vect2& dim);

        void setBorder(chtype ul = ACS_ULCORNER, chtype top = ACS_HLINE, chtype ur = ACS_URCORNER,
                       chtype left = ACS_VLINE, chtype fill = ' ', chtype right = ACS_VLINE,
                       chtype ll = ACS_LLCORNER, chtype bottom = ACS_HLINE, chtype lr = ACS_LRCORNER);


        void setUpperLeft(const chtype& upperLeft);
        void setUpperRight(const chtype& upperRight);
        void setUpper(const chtype& upper);
        void setLower(const chtype& lower);
        void setLowerLeft(const chtype& lowerLeft);
        void setLowerRight(const chtype& lowerRight);
        void setLeft(const chtype& left);
        void setRight(const chtype& right);
        void setFill(const chtype& fill);

        void initialize() override;
        void render() override;

    private:

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


}

#endif //CURSEN_BOX_H
