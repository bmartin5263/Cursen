//
// Created by Brandon Martin on 6/30/19.
//

#include <cassert>
#include <Cursen/Drawing/CursesManager.h>

#include "HorizontalLine.h"

namespace cursen {

    HorizontalLine::HorizontalLine() :
            StandardComponent(Vect2(0,0), Vect2(0,0))
    {

    }

    HorizontalLine::HorizontalLine(const Vect2& pos) :
            StandardComponent(pos, Vect2(0,1))
    {

    }

    void HorizontalLine::initialize()
    {
        StandardComponent::initialize();
        line_char = CursesManager::HLINE;
        right_marker = CursesManager::RTEE;
        left_marker = CursesManager::LTEE;
    }

    void HorizontalLine::render()
    {
        StandardComponent::render();
        Content& content = getContent();
        Vect2 dimensions = content.getSize();

        if (dimensions.x >= 0)
        {
            ColorPair& draw_color = getCurrentDrawColor();
            content.clear();

            chtype line[dimensions.x];
            line[0] = left_marker | draw_color;
            line[dimensions.x - 1] = right_marker | draw_color;
            for (int i = 1; i < dimensions.x - 1; i++)
            {
                line[i] = line_char | draw_color;
            }

            content.writeLine(line, Vect2(0,0));
        }

    }

    void HorizontalLine::setLength(int len)
    {
        StandardComponent::setSize(Vect2(len, 1));
    }

    void HorizontalLine::setSize(const Vect2& size)
    {
        (void)size;
        assert(false);
    }

}
