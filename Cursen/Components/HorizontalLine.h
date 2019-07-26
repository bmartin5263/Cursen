//
// Created by Brandon Martin on 6/30/19.
//

#ifndef CURSEN_HORIZONTALLINE_H
#define CURSEN_HORIZONTALLINE_H

#include "Cursen/Components/StandardComponent.h"

namespace cursen
{
    class HorizontalLine : public cursen::StandardComponent
    {

    public:

        HorizontalLine();
        HorizontalLine(const Vect2& pos);

        void initialize() override;
        void render() override;

        void setLength(int len);

    private:

        void setSize(const Vect2& size) override ;

        chtype left_marker;
        chtype right_marker;
        chtype line_char;


    };
}



#endif //CURSEN_HORIZONTALLINE_H
