//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_CARD_H
#define CURSEN_CARD_H

#include <string>
#include <vector>

#include <Cursen/Drawing/Color.h>
#include <unordered_map>
#include <Uno/Messages/Serializable.h>
#include "CardColor.h"
#include "CardValues.h"
#include "Cursen/Events/Event.h"

class Card : public Serializable {

private:

    static const std::unordered_map<CardValues, std::vector<std::string>, cursen::EnumClassHash> BIG_NUMBERS;

public:

    static const CardColor COLORS[4];
    static const CardValues VALUES_NO_WILD[13];

    static int score(const Card& card);
    static cursen::Color ConvertToColor(CardColor color);
    static std::string getUpperLabel(CardValues value);
    static std::string getLowerLabel(CardValues value);
    static const std::vector<std::string>& GetBigNumber(CardValues value);

    Card();
    Card(CardColor color, CardValues value);
    Card(CardColor color, CardValues value, bool wildOverride);

    bool operator == (const Card & other) const;

    bool isWild() const;
    Card changeColor(CardColor color) const;

    CardColor getColor() const;
    CardValues getValue() const;
    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

private:

    CardColor color;
    CardValues value;
    bool wild;

};


#endif //CURSEN_CARD_H
