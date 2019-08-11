//
// Created by Brandon Martin on 4/14/19.
//

#ifndef CURSEN_CONSTANTS_H
#define CURSEN_CONSTANTS_H

#include "GameObjects/PlayerColor.h"

#include <string>

class Constants {

public:

    const static int NUM_COLORS = 6;
    const static PlayerColor COLORS[NUM_COLORS];
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

};

struct EnumHash {
    template<typename T>
    std::size_t operator()(T t) const {
        return static_cast<std::size_t>(t);
    }
};

#endif //CURSEN_CONSTANTS_H
