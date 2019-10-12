//
// Created by Brandon Martin on 10/10/19.
//

#include "BoardMeter.h"

using namespace cursen;

BoardMeter::BoardMeter() : filled_index(20)
{

}

void BoardMeter::initialize()
{
    border.initialize();
    border.setSize(Vect2(3,22));
    addRelative(border);

    meter.initialize();
    meter.setSize(Vect2(1,20));
    meter.setPosition(border.getPosition() + Vect2(1,1));
    meter.drawOnTopOf(border);
    addRelative(meter);
}

void BoardMeter::fill(int amt)
{
    if (filled_index > 0)
    {
        int current_index = filled_index - 1;
        amt = (filled_index) < amt ? filled_index : amt;
        filled_index = (filled_index - amt);
        for (int i = current_index; i >= filled_index; --i)
        {
            meter[i][0] = ' ' | ColorPair(Color::BLACK, Color::MAGENTA);
        }
    }
}

void BoardMeter::spill(int amt)
{
    if (filled_index < 20)
    {
        int current_index = filled_index;
        amt = 20 - filled_index < amt ? 20 - filled_index : amt;
        filled_index = filled_index + amt;
        for (int i = current_index; i < filled_index; ++i)
        {
            meter[i][0] = ' ' | ColorPair(Color::BLACK, Color::BLACK);
        }
    }
}
