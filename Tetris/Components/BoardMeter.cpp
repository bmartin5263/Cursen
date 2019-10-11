//
// Created by Brandon Martin on 10/10/19.
//

#include "BoardMeter.h"

using namespace cursen;

BoardMeter::BoardMeter()
{

}

void BoardMeter::initialize()
{
    border.initialize();
    border.setSize(Vect2(3,22));
    addRelative(border);
}
