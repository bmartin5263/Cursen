//
// Created by Brandon Martin on 3/12/19.
//

#include "Color.h"
#include "CursesManager.h"

namespace cursen {

    const short Color::BLK = 0;
    const short Color::WHT = 231;

    const Color Color::NONE = Color(-1);            // Null Color
    const Color Color::BLACK = Color(BLK);
    const Color Color::WHITE = Color(WHT);
    const Color Color::GRAY = Color(241);
    const Color Color::DARK_GRAY = Color(16);
    const Color Color::RED = Color(199);
    const Color Color::BLUE = Color(39);
    const Color Color::DARK_BLUE = Color(21);
    const Color Color::PURPLE = Color(57);
    const Color Color::VIOLET = Color(93);
    const Color Color::INDIGO = Color(21);
    const Color Color::LAVENDER = Color(63);
    const Color Color::GREEN = Color(82);
    const Color Color::YELLOW = Color(226);
    const Color Color::ORANGE = Color(208);


    Color::Color() :
            val(CursenApplication::GetColorPalette().getForeground().val) {
    }

    Color::Color(short value) :
            val(value) {
    }

    Color::Color(const Color &other) {
        this->val = other.val;
    }

    Color Color::RandomColor() {
        int randNum = (rand() % 4);
        if (randNum == 0) return BLUE;
        if (randNum == 1) return RED;
        if (randNum == 2) return GREEN;
        if (randNum == 3) return YELLOW;
        return Color();
    }

    Color &Color::operator=(const Color &other) {
        this->val = other.val;
        return *this;
    }

    short Color::getValue() {
        return val;
    }

}

chtype operator|(chtype c, const cursen::Color &n) {
    if (n.val == -1) return c;
    return c | cursen::CursesManager::GetColorPair(cursen::ColorPair(n));
}

chtype operator|(const cursen::Color &n, chtype c) {
    if (n.val == -1) return c;
    return c | cursen::CursesManager::GetColorPair(cursen::ColorPair(n));
}

chtype& operator |= (chtype& c, const cursen::Color &n) {
    if (n.val != -1) c |= cursen::CursesManager::GetColorPair(cursen::ColorPair(n));
    return c;
}

chtype operator^(chtype c, const cursen::Color &n) {
    if (n.val == -1) return c;
    short pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(n));
    if ((pair & c) > 0) return c ^ pair;
    return c;
}

chtype operator^(const cursen::Color &n, chtype c) {
    if (n.val == -1) return c;
    short pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(n));
    if ((pair & c) > 0) return c ^ pair;
    return c;
}

chtype& operator ^= (chtype& c, const cursen::Color &n) {
    if (n.val == -1) return c;
    short pair = cursen::CursesManager::GetColorPair(cursen::ColorPair(n));
    if ((pair & c) > 0) c ^= pair;
    return c;
}

bool cursen::Color::operator==(const cursen::Color &other) const {
    return this->val == other.val;
}

bool cursen::Color::operator!=(const cursen::Color &other) const {
    return this->val != other.val;
}