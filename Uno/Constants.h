//
// Created by Brandon Martin on 4/14/19.
//

#ifndef CURSEN_CONSTANTS_H
#define CURSEN_CONSTANTS_H

#include "GameObjects/PlayerColor.h"

#include <string>
#include <Uno/GameObjects/CardColor.h>
#include <random>
#include <netinet/in.h>
#include <arpa/inet.h>

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

    Constants();
    int getRandomNumber();

    static Constants& Instance() {
        static Constants instance;
        return instance;
    }

    const static int NUM_PLAYER_COLORS = 6;
    const static int NUM_CARD_COLORS = 4;
    const static PlayerColor PLAYER_COLORS[NUM_PLAYER_COLORS];
    const static CardColor CARD_COLORS[NUM_CARD_COLORS];
    const static int MAX_NAME_LEN = 12;
    const static char* WHITESPACE;

    std::random_device rd;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;

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
        int index = Instance().getRandomNumber();
        CardColor color = CARD_COLORS[index];
        while (exclude != CardColor::WHITE && color == exclude)
        {
            index = Instance().getRandomNumber();
            color = CARD_COLORS[index];
        }
        return color;
    }

    static bool validateIPv4(const std::string& ip)
    {
        sockaddr_in sa;
        return inet_pton(AF_INET, ip.c_str(), &(sa.sin_addr))!=0;
    }

    static bool validateIPv6(const std::string& str)
    {
        sockaddr_in6 sa;
        return inet_pton(AF_INET6, str.c_str(), &(sa.sin6_addr))!=0;
    }

};

#endif //CURSEN_CONSTANTS_H
