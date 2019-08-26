//
// Created by Brandon Martin on 4/15/19.
//

#include "Constants.h"

const PlayerColor Constants::PLAYER_COLORS[NUM_PLAYER_COLORS] = {
        PlayerColor::BLUE,
        PlayerColor::RED,
        PlayerColor::GREEN,
        PlayerColor::YELLOW,
        PlayerColor::PURPLE,
        PlayerColor::ORANGE
};

const CardColor Constants::CARD_COLORS[NUM_CARD_COLORS] = {
        CardColor::BLUE,
        CardColor::RED,
        CardColor::GREEN,
        CardColor::YELLOW,
};


const char* Constants::WHITESPACE = " \n\r\t\f\v";

Constants::Constants() :
        generator(rd()), distribution(0,3)
{
}

int Constants::getRandomNumber()
{
    return distribution(generator);
}
