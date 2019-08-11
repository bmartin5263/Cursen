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
#include "CardValue.h"
#include "Cursen/Events/Event.h"

class Card : public Serializable {

private:

    static const std::unordered_map<CardValue, std::vector<std::string>, cursen::EnumClassHash> BIG_NUMBERS;

public:

    static const CardColor COLORS[4];
    static const CardValue VALUES_NO_WILD[13];

    static int score(const Card& card);
    static cursen::Color ConvertToColor(CardColor color);
    static std::string getUpperLabel(CardValue value);
    static std::string getLowerLabel(CardValue value);
    static const std::vector<std::string>& GetBigNumber(CardValue value);

    Card();
    Card(CardColor color, CardValue value);
    Card(CardColor color, CardValue value, bool wildOverride);

    bool operator == (const Card & other) const;
    bool operator != (const Card & other) const;

    bool isWild() const;
    Card changeColor(CardColor color) const;

    CardColor getColor() const;
    CardValue getValue() const;
    size_t serialize(char* const buffer) const override;
    size_t deserialize(const char* const buffer) override;
    size_t sizeOf() const override;

private:

    CardColor color;
    CardValue value;
    bool wild;

};


#endif //CURSEN_CARD_H
