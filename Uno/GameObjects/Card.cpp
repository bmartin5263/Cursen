//
// Created by Brandon Martin on 4/5/19.
//

#include "Card.h"

const CardColors Card::COLORS[4] = {CardColors::BLUE, CardColors::RED, CardColors::GREEN, CardColors::YELLOW};
const CardValues Card::VALUES_NO_WILD[13] = {
        CardValues::ZERO, CardValues::ONE, CardValues::TWO, CardValues::THREE, CardValues::FOUR,
        CardValues::FIVE, CardValues::SIX, CardValues::SEVEN, CardValues::EIGHT, CardValues::NINE,
        CardValues::SKIP, CardValues::REVERSE, CardValues::PLUS_2
};

const std::unordered_map<CardValues, std::vector<std::string>, cursen::EnumClassHash> Card::BIG_NUMBERS = {

        {CardValues::ZERO, {"  .d8888b.  ", " d88P  Y88b ", " 888    888 ", " 888    888 ", " 888    888 ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValues::ONE, {"   .d888    ", "  d88888    ", "    8888    ", "    8888    ", "    8888    ", "    8888    ","    8888    ", "  88888888  "}},
        {CardValues::TWO, {"  .d8888b.  ", " d88P  Y88b ", "        888 ", "      .d88P ", "  .od888P\"  ", " d88P\"      "," 888\"       ", " 8888888888 "}},
        {CardValues::THREE, {"  .d8888b.  ", " d88P  Y88b ", "      .d88P ", "     8888\"  ", "      \"Y8b. ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValues::FOUR, {"     d8888  ", "    d8P888  ", "   d8P 888  ", "  d8P  888  ", " d88   888  ", " 8888888888 ","       888  ", "       888  "}},
        {CardValues::FIVE, {" 8888888888 ", " 888        ", " 888        ", " 8888888b.  ", "      \"Y88b ", "        888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValues::SIX, {"  .d8888b.  ", " d88P  Y88b ", " 888        ", " 888d888b.  ", " 888P \"Y88b ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValues::SEVEN, {" 8888888888 ", "       d88P ", "      d88P  ", "     d88P   ", "  88888888  ", "   d88P     ","  d88P      ", " d88P       "}},
        {CardValues::EIGHT, {"  .d8888b.  ", " d88P  Y88b ", " Y88b. d88P ", "  \"Y88888\"  ", " .d8P\"\"Y8b. ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValues::NINE, {"  .d8888b.  ", " d88P  Y88b ", " 888    888 ", " Y88b. d888 ", "  \"Y888P888 ", "        888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValues::SKIP, {" Y8b    d8P ", "  Y8b  d8P  ", "   Y8888P   ", "    Y88P    ", "    d88b    ", "   d8888b   ","  d8P  Y8b  ", " d8P    Y8b "}},
        {CardValues::REVERSE, {"   Y88b     ", "    Y88b    ", "     Y88b   ", "      Y88b  ", "      d88P  ", "     d88P   ","    d88P    ", "   d88P     "}},
        {CardValues::PLUS_2, {"   db       ", "   88       ", " C8888D     ", "   88  8888 ", "   VP     8 ", "       8888 ","       8    ", "       8888 "}},
        {CardValues::PLUS_4, {"   db       ", "   88       ", " C8888D     ", "   88    d  ", "   VP   d8  ", "       d 8  ","      d8888 ", "         8  "}},
        {CardValues::WILD, {" 88      88 ", " 88      88 ", " 88  db  88 ", " 88 d88b 88 ", " 88d8888b88 ", " 88P    Y88 "," 8P      Y8 ", " P        Y "}},

};

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
    color(color), value(value), wild(value == CardValues::PLUS_4 || value == CardValues::WILD)
{
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

cursen::Color Card::ConvertToColor(CardColors color)
{
    switch (color)
    {
        case CardColors::BLUE:
            return cursen::Color::BLUE;
        case CardColors::RED:
            return cursen::Color::RED;
        case CardColors::GREEN:
            return cursen::Color::GREEN;
        case CardColors::YELLOW:
            return cursen::Color::YELLOW;
        case CardColors::WHITE:
            return cursen::Color::WHITE;
    }
}

std::string Card::getUpperLabel(CardValues value)
{
    switch (value)
    {
        case CardValues::ZERO:
            return " 0";
        case CardValues::ONE:
            return " 1";
        case CardValues::TWO:
            return " 2";
        case CardValues::THREE:
            return " 3";
        case CardValues::FOUR:
            return " 4";
        case CardValues::FIVE:
            return " 5";
        case CardValues::SIX:
            return " 6";
        case CardValues::SEVEN:
            return " 7";
        case CardValues::EIGHT:
            return " 8";
        case CardValues::NINE:
            return " 9";
        case CardValues::PLUS_2:
            return "+2";
        case CardValues::PLUS_4:
            return "+4";
        case CardValues::WILD:
            return " W";
        case CardValues::SKIP:
            return " X";
        case CardValues::REVERSE:
            return " R";
    }
}

std::string Card::getLowerLabel(CardValues value)
{
    switch (value)
    {
        case CardValues::ZERO:
            return "0 ";
        case CardValues::ONE:
            return "1 ";
        case CardValues::TWO:
            return "2 ";
        case CardValues::THREE:
            return "3 ";
        case CardValues::FOUR:
            return "4 ";
        case CardValues::FIVE:
            return "5 ";
        case CardValues::SIX:
            return "6 ";
        case CardValues::SEVEN:
            return "7 ";
        case CardValues::EIGHT:
            return "8 ";
        case CardValues::NINE:
            return "9 ";
        case CardValues::PLUS_2:
            return "+2";
        case CardValues::PLUS_4:
            return "+4";
        case CardValues::WILD:
            return "W ";
        case CardValues::SKIP:
            return "X ";
        case CardValues::REVERSE:
            return "R ";
    }
}

const std::vector<std::string>& Card::GetBigNumber(CardValues value)
{
    return Card::BIG_NUMBERS.at(value);
}
