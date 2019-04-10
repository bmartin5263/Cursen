//
// Created by Brandon Martin on 4/5/19.
//

#include "Card.h"

int Card::score(const Card &card) {
    switch (card.getValue()) {
        case CardValues::ZERO:
            return 0;
        case CardValues::ONE:
            return 1;
        case CardValues::TWO:
            return 2;
        case CardValues::THREE:
            return 3;
        case CardValues::FOUR:
            return 4;
        case CardValues::FIVE:
            return 5;
        case CardValues::SIX:
            return 6;
        case CardValues::SEVEN:
            return 7;
        case CardValues::EIGHT:
            return 8;
        case CardValues::NINE:
            return 9;
        case CardValues::WILD:
        case CardValues::PLUS_4:
            return 50;
        default:                    // skip, reverse, plus2
            return 20;
    }
}

Card::Card(CardColors color, CardValues value) :
    color(color), value(value), wild(false)
{
    if (value == CardValues::PLUS_4 || value == CardValues::WILD) {
        wild = true;
    }
}

bool Card::operator == (const Card &other) const {
    return color == other.color && value == other.value && wild == other.wild;
}

CardValues Card::getValue() const {
    return value;
}

CardColors Card::getColor() const {
    return color;
}

bool Card::isWild() const {
    return wild;
}

void Card::changeColor(const CardColors &new_color) {
    if (wild) {
        wild = false;
        color = new_color;
    }
}
