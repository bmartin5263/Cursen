//
// Created by Brandon Martin on 4/5/19.
//

#include "Card.h"

const CardColor Card::COLORS[4] = {CardColor::BLUE, CardColor::RED, CardColor::GREEN, CardColor::YELLOW};
const CardValue Card::VALUES_NO_WILD[13] = {
        CardValue::ZERO, CardValue::ONE, CardValue::TWO, CardValue::THREE, CardValue::FOUR,
        CardValue::FIVE, CardValue::SIX, CardValue::SEVEN, CardValue::EIGHT, CardValue::NINE,
        CardValue::SKIP, CardValue::REVERSE, CardValue::PLUS_2
};

const std::unordered_map<CardValue, std::vector<std::string>, cursen::EnumClassHash> Card::BIG_NUMBERS = {

        {CardValue::ZERO, {"  .d8888b.  ", " d88P  Y88b ", " 888    888 ", " 888    888 ", " 888    888 ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValue::ONE, {"   .d888    ", "  d88888    ", "    8888    ", "    8888    ", "    8888    ", "    8888    ","    8888    ", "  88888888  "}},
        {CardValue::TWO, {"  .d8888b.  ", " d88P  Y88b ", "        888 ", "      .d88P ", "  .od888P\"  ", " d88P\"      "," 888\"       ", " 8888888888 "}},
        {CardValue::THREE, {"  .d8888b.  ", " d88P  Y88b ", "      .d88P ", "     8888\"  ", "      \"Y8b. ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValue::FOUR, {"     d8888  ", "    d8P888  ", "   d8P 888  ", "  d8P  888  ", " d88   888  ", " 8888888888 ","       888  ", "       888  "}},
        {CardValue::FIVE, {" 8888888888 ", " 888        ", " 888        ", " 8888888b.  ", "      \"Y88b ", "        888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValue::SIX, {"  .d8888b.  ", " d88P  Y88b ", " 888        ", " 888d888b.  ", " 888P \"Y88b ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValue::SEVEN, {" 8888888888 ", "       d88P ", "      d88P  ", "     d88P   ", "  88888888  ", "   d88P     ","  d88P      ", " d88P       "}},
        {CardValue::EIGHT, {"  .d8888b.  ", " d88P  Y88b ", " Y88b. d88P ", "  \"Y88888\"  ", " .d8P\"\"Y8b. ", " 888    888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValue::NINE, {"  .d8888b.  ", " d88P  Y88b ", " 888    888 ", " Y88b. d888 ", "  \"Y888P888 ", "        888 "," Y88b  d88P ", "  \"Y8888P\"  "}},
        {CardValue::SKIP, {" Y8b    d8P ", "  Y8b  d8P  ", "   Y8888P   ", "    Y88P    ", "    d88b    ", "   d8888b   ","  d8P  Y8b  ", " d8P    Y8b "}},
        {CardValue::REVERSE, {"   Y88b     ", "    Y88b    ", "     Y88b   ", "      Y88b  ", "      d88P  ", "     d88P   ","    d88P    ", "   d88P     "}},
        {CardValue::PLUS_2, {"   db       ", "   88       ", " C8888D     ", "   88  8888 ", "   VP     8 ", "       8888 ","       8    ", "       8888 "}},
        {CardValue::PLUS_4, {"   db       ", "   88       ", " C8888D     ", "   88    d  ", "   VP   d8  ", "       d 8  ","      d8888 ", "         8  "}},
        {CardValue::WILD, {" 88      88 ", " 88      88 ", " 88  db  88 ", " 88 d88b 88 ", " 88d8888b88 ", " 88P    Y88 "," 8P      Y8 ", " P        Y "}},

};

const std::vector<std::vector<std::string>> Card::BIG_REVERSE =
{
        {"     d88P   ", "    d88P    ", "   d88P     ", "  d88P      ", "  Y88b      ", "   Y88b     ", "    Y88b    ", "     Y88b   "},
        {"    d88P   Y", "   d88P     ", "  d88P      ", " d88P       ", " Y88b       ", "  Y88b      ", "   Y88b     ", "    Y88b   d"},
        {"   d88P   Y8", "  d88P     Y", " d88P       ", "d88P        ", "Y88b        ", " Y88b       ", "  Y88b     d", "   Y88b   d8"},
        {"  d88P   Y88", " d88P     Y8", "d88P       Y", "88P         ", "88b         ", "Y88b       d", " Y88b     d8", "  Y88b   d88"},
        {" d88P   Y88b", "d88P     Y88", "88P       Y8", "8P         Y", "8b         d", "88b       d8", "Y88b     d88", " Y88b   d88P"},
        {"d88P   Y88b ", "88P     Y88b", "8P       Y88", "P         Y8", "b         d8", "8b       d88", "88b     d88P", "Y88b   d88P "},
        {"88P   Y88b  ", "8P     Y88b ", "P       Y88b", "         Y88", "         d88", "b       d88P", "8b     d88P ", "88b   d88P  "},
        {"8P   Y88b   ", "P     Y88b  ", "       Y88b ", "        Y88b", "        d88P", "       d88P ", "b     d88P  ", "8b   d88P   "},
        {"P   Y88b    ", "     Y88b   ", "      Y88b  ", "       Y88b ", "       d88P ", "      d88P  ", "     d88P   ", "b   d88P    "},
        {"   Y88b     ", "    Y88b    ", "     Y88b   ", "      Y88b  ", "      d88P  ", "     d88P   ", "    d88P    ", "   d88P     "}
};

int Card::score(const Card &card) {
    switch (card.getValue()) {
        case CardValue::ZERO:
            return 0;
        case CardValue::ONE:
            return 1;
        case CardValue::TWO:
            return 2;
        case CardValue::THREE:
            return 3;
        case CardValue::FOUR:
            return 4;
        case CardValue::FIVE:
            return 5;
        case CardValue::SIX:
            return 6;
        case CardValue::SEVEN:
            return 7;
        case CardValue::EIGHT:
            return 8;
        case CardValue::NINE:
            return 9;
        case CardValue::WILD:
        case CardValue::PLUS_4:
            return 50;
        default:                    // skip, reverse, plus2
            return 20;
    }
}

Card::Card() :
    color(CardColor::WHITE), value(CardValue::ZERO), wild(false)
{

}


Card::Card(CardColor color, CardValue value) :
        color(color), value(value), wild(value == CardValue::PLUS_4 || value == CardValue::WILD)
{
}

Card::Card(CardColor color, CardValue value, bool wildOverride) :
        color(color), value(value), wild(wildOverride)
{
}

bool Card::operator == (const Card &other) const {
    return color == other.color && value == other.value && wild == other.wild;
}

bool Card::operator!=(const Card& other) const
{
    return !(*this == other);
}


CardValue Card::getValue() const {
    return value;
}

CardColor Card::getColor() const {
    return color;
}

bool Card::isWild() const {
    return wild;
}

Card Card::changeColor(CardColor new_color) const {
    if (wild) {
        return Card(new_color, this->value, false);
    }
    return *this;
}

cursen::Color Card::ConvertToColor(CardColor color)
{
    switch (color)
    {
        case CardColor::BLUE:
            return cursen::Color::BLUE;
        case CardColor::RED:
            return cursen::Color::RED;
        case CardColor::GREEN:
            return cursen::Color::GREEN;
        case CardColor::YELLOW:
            return cursen::Color::YELLOW;
        case CardColor::WHITE:
            return cursen::Color::WHITE;
    }
}

std::string Card::getUpperLabel(CardValue value)
{
    switch (value)
    {
        case CardValue::ZERO:
            return " 0";
        case CardValue::ONE:
            return " 1";
        case CardValue::TWO:
            return " 2";
        case CardValue::THREE:
            return " 3";
        case CardValue::FOUR:
            return " 4";
        case CardValue::FIVE:
            return " 5";
        case CardValue::SIX:
            return " 6";
        case CardValue::SEVEN:
            return " 7";
        case CardValue::EIGHT:
            return " 8";
        case CardValue::NINE:
            return " 9";
        case CardValue::PLUS_2:
            return "+2";
        case CardValue::PLUS_4:
            return "+4";
        case CardValue::WILD:
            return " W";
        case CardValue::SKIP:
            return " X";
        case CardValue::REVERSE:
            return " R";
    }
}

std::string Card::getLowerLabel(CardValue value)
{
    switch (value)
    {
        case CardValue::ZERO:
            return "0 ";
        case CardValue::ONE:
            return "1 ";
        case CardValue::TWO:
            return "2 ";
        case CardValue::THREE:
            return "3 ";
        case CardValue::FOUR:
            return "4 ";
        case CardValue::FIVE:
            return "5 ";
        case CardValue::SIX:
            return "6 ";
        case CardValue::SEVEN:
            return "7 ";
        case CardValue::EIGHT:
            return "8 ";
        case CardValue::NINE:
            return "9 ";
        case CardValue::PLUS_2:
            return "+2";
        case CardValue::PLUS_4:
            return "+4";
        case CardValue::WILD:
            return "W ";
        case CardValue::SKIP:
            return "X ";
        case CardValue::REVERSE:
            return "R ";
    }
}

const std::vector<std::string>& Card::GetBigNumber(CardValue value)
{
    return Card::BIG_NUMBERS.at(value);
}

const std::vector<std::string>& Card::GetReverse(int index)
{
    return Card::BIG_REVERSE[index];
}


size_t Card::serialize(char* const buffer) const
{
    size_t written = 0;

    written += Serializable::Serialize(buffer + written, (int)color);
    written += Serializable::Serialize(buffer + written, (int)value);
    written += Serializable::Serialize(buffer + written, wild);

    return written;
}

size_t Card::deserialize(const char* const buffer)
{
    size_t read = 0;

    int raw_color;
    read += Serializable::Deserialize(buffer + read, raw_color);
    color = (CardColor)raw_color;
    int raw_val;
    read += Serializable::Deserialize(buffer + read, raw_val);
    value = (CardValue)raw_val;
    read += Serializable::Deserialize(buffer + read, wild);

    return read;
}

size_t Card::sizeOf() const
{
    return sizeof(Card);
}