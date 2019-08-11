//
// Created by Brandon Martin on 7/4/19.
//

#include "HandMeter.h"

HandMeter::HandMeter() :
    AggregateComponent()
{

}

HandMeter::HandMeter(cursen::Vect2 pos) :
    AggregateComponent(pos)
{

}

void HandMeter::initialize()
{
    meter.initialize();
    meter.setText("[]");
    addRelative(meter);
}

void HandMeter::update(int hand_size, int hand_index)
{
    if (hand_size == 0) meter.setText("[]");
    else
    {
        std::string new_meter = "[";
        int hand_indices = ((hand_size - 1) / 14) + 1;
        for (int i = 0; i < hand_indices; ++i)
        {
            if (i == hand_index) new_meter += std::string("|");
            else new_meter += std::string("-");
        }
        meter.setText(new_meter + "]");
    }

}
