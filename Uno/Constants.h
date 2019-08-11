//
// Created by Brandon Martin on 4/14/19.
//

#ifndef CURSEN_CONSTANTS_H
#define CURSEN_CONSTANTS_H

#include "GameObjects/PlayerColor.h"

#include <string>
#include <Uno/GameObjects/CardColor.h>
#include <random>

struct RNG {
    int operator() (int n) {
        return (int)(std::rand() / (1.0 + RAND_MAX) * n);
    }
};

struct EnumHash {
    template<typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

class Constants {

public:

    const static int NUM_PLAYER_COLORS = 6;
    const static int NUM_CARD_COLORS = 4;
    const static PlayerColor PLAYER_COLORS[NUM_PLAYER_COLORS];
    const static CardColor CARD_COLORS[NUM_CARD_COLORS];
    const static int MAX_NAME_LEN = 12;
    const static char* WHITESPACE;

    int turnOffK(int n, int k)
    {
        if (k <= 0) return n;
        return (n & ~(1 << (k - 1)));
    }

    static std::string rtrim(const std::string& s)
    {
        size_t end = s.find_last_not_of(WHITESPACE);
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    static void padLeft(std::string& str, int length)
    {
        if ( str.size() < length )
        {
            str = std::string(length - str.size(), ' ') + str;
        }
    }

    static void padRight(std::string& str, int length)
    {
        if ( str.size() < length )
        {
            str = str + std::string(length - str.size(), ' ');
        }
    }

    static CardColor getRandomCardColor(CardColor exclude = CardColor::WHITE)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0,4);
        CardColor color = CARD_COLORS[distribution(generator)];
        while (exclude != CardColor::WHITE && color == exclude)
        {
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(0,4);
            color = CARD_COLORS[distribution(generator)];
        }
        return color;
    }

};

#endif //CURSEN_CONSTANTS_H
