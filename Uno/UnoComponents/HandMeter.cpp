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
    addRelative(&meter);
}
