//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_CARD_H
#define CURSEN_CARD_H

#include <string>

#include <Cursen/Drawing/Color.h>
#include "CardColors.h"
#include "CardValues.h"

class Card {

public:

    static int score(const Card& card);
    static cursen::Color convertToColor(CardColors color);
    static std::string getUpperLabel(CardValues value);
    static std::string getLowerLabel(CardValues value);

    Card(CardColors color, CardValues value);

    bool operator == (const Card & other) const;

    bool isWild() const;
    void changeColor(const CardColors& color);

    CardColors getColor() const;
    CardValues getValue() const;

private:

    CardColors color;
    CardValues value;
    bool wild;

};


#endif //CURSEN_CARD_H
