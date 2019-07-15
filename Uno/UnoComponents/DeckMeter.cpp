//
// Created by Brandon Martin on 6/30/19.
//

#include <assert.h>
#include <Uno/GameObjects/Deck.h>
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

    low_deck.setFrameDuration(.6);
    low_deck.add([&]() { border.setForeground(Color::RED); });
    low_deck.add([&]() { border.setForeground(Color::WHITE); });
}

void DeckMeter::setDeckSize(size_t size)
{
    meter.setDeckSize(size);
}

void DeckMeter::setCardCount(size_t count)
{
    assert(count <= Deck::SIZE);
    meter.setCardCount(count);
    if (count == 0)
    {
        low_deck.stop();
        border.setForeground(Color::GRAY);
    }
    else if (count <= 36)
    {
        low_deck.start();
    }
    else
    {
        low_deck.stop();
        border.setForeground(Color::WHITE);
    }
}
