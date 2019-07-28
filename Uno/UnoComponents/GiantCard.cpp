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

void GiantCard::injectCard(const Card& card)
{
    value = card.getValue();
    number.loadFromVector(Card::GetBigNumber(card.getValue()));
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

void GiantCard::setValuesFrom(GiantCard& giantCard)
{
    this->color = giantCard.color;
    this->value = giantCard.value;
    number.loadFromVector(Card::GetBigNumber(this->value));
    setForeground(Card::ConvertToColor(color));
    if (isHidden()) setHidden(false);
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
