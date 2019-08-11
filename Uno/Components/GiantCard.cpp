//
// Created by Brandon Martin on 7/5/19.
//

#include <Uno/GameObjects/Card.h>
#include "GiantCard.h"

using namespace cursen;

GiantCard::GiantCard() : card_injected(false)
{

}

GiantCard::GiantCard(const cursen::Vect2& pos) : AggregateComponent(pos), card_injected(false)
{

}

void GiantCard::initialize()
{
    border.initialize();
    border.setSize(Vect2(14, 12));
    addRelative(border);

    number.initialize();
    number.setPosition(Vect2(1,2));
    number.drawOnTopOf(border);
    addRelative(number);
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

void GiantCard::injectCard(const Card& card, bool reversed)
{
    value = card.getValue();
    if (value == CardValue::REVERSE)
    {
        if (reversed) number.loadFromVector(Card::GetReverse(0));
        else number.loadFromVector(Card::GetReverse(9));
    }
    else
    {
        number.loadFromVector(Card::GetBigNumber(value));
    }
    if (card.isWild()) {
        setForeground(Color::WHITE);
        color = CardColor::WHITE;
    }
    else {
        setForeground(Card::ConvertToColor(card.getColor()));
        color = card.getColor();
    }
    card_injected = true;
}

void GiantCard::setReverseFace(int index)
{
    number.loadFromVector(Card::GetReverse(index));
}

void GiantCard::setValuesFrom(GiantCard& giantCard, bool reversed)
{
    this->color = giantCard.color;
    this->value = giantCard.value;
    if (this->value == CardValue::REVERSE)
    {
        if (reversed) number.loadFromVector(Card::GetReverse(0));
        else number.loadFromVector(Card::GetReverse(9));
    }
    else
    {
        number.loadFromVector(Card::GetBigNumber(this->value));
    }
    setForeground(Card::ConvertToColor(color));
    border.setHidden(false);
    number.setHidden(false);
    card_injected = true;
}

void GiantCard::shrinkCompletely()
{
    number.setHidden(true);
    setSize(Vect2(4,2));
}

void GiantCard::setNumberHidden(bool value)
{
    this->number.setHidden(value);
}

void GiantCard::setHidden(bool value)
{
    border.setHidden(value);
}

bool GiantCard::hasCardInjected()
{
    return card_injected;
}
