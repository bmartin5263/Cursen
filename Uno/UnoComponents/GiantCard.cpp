//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/GameObjects/Card.h>
#include "GiantCard.h"

using namespace cursen;

GiantCard::GiantCard()
{

}

GiantCard::GiantCard(const cursen::Vect2& pos) : AggregateComponent(pos)
{

}

void GiantCard::initialize()
{
    border.initialize();
    border.setSize(Vect2(14, 12));
    addRelative(&border);

    number.initialize();
    number.setHidden(false);
    number.setPosition(Vect2(1,2));
    number.loadFromVector(Card::BIG_NUMBERS.find(CardValues::SIX)->second);
    number.setForeground(Color::RED);
    number.drawOnTopOf(border);
    addRelative(&number);
}

void GiantCard::setSize(const cursen::Vect2& size)
{
    border.setSize(size);
}

void GiantCard::shrink()
{
    border.setSize(border.getSize() - Vect2(1,1));
}

void GiantCard::grow()
{
    border.setSize(border.getSize() + Vect2(1,1));
}
