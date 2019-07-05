//
// Created by Brandon Martin on 6/30/19.
//

#include "DeckMeter.h"

using namespace cursen;

DeckMeter::DeckMeter() :
    AggregateComponent()
{

}

DeckMeter::DeckMeter(cursen::Vect2 pos) :
    AggregateComponent(pos)
{

}

void DeckMeter::initialize()
{
    border.initialize();
    border.setPosition(Vect2(0,0));
    border.setSize(Vect2(5, 11));
    addRelative(&border);

    meter.initialize();
    meter.setPosition(Vect2(2,1));
    addRelative(&meter);
}

void DeckMeter::setDeckSize(int size)
{
    meter.setDeckSize(size);
}

void DeckMeter::setCardCount(int count)
{
    meter.setCardCount(count);
}
