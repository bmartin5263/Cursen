//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_CARD_H
#define CURSEN_CARD_H

#include <string>
#include <vector>

#include <Cursen/Drawing/Color.h>
#include <unordered_map>
#include "CardColors.h"
#include "CardValues.h"
#include "Cursen/Events/Event.h"

class Card {

public:

    static const std::unordered_map<CardValues, std::vector<std::string>, cursen::EnumClassHash> BIG_NUMBERS;
    static const CardColors COLORS[4];
    static const CardValues VALUES_NO_WILD[13];

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
