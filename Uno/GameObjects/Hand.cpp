//
// Created by Brandon Martin on 4/5/19.
//

#include "Hand.h"

const Card &Hand::get(int index)
{
    return cards[index];
}

void Hand::add(const Card & card)
{
    cards.push_back(card);
}

unsigned long Hand::size() const
{
    return cards.size();
}

bool Hand::empty() const
{
    return cards.empty();
}

void Hand::remove(int index)
{
    cards.erase(cards.begin() + index);
}
