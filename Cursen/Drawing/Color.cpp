//
// Created by Brandon Martin on 3/12/19.
//

#include "Color.h"
#include "CursesManager.h"

const short Color::BLK = 0;
const short Color::WHT = 15;

const Color Color::NONE = Color(-1, -1);            // Null Color
const Color Color::BLACK = Color(BLK, BLK);
const Color Color::WHITE = Color(WHT, BLK);
const Color Color::GRAY = Color(8, BLK);
const Color Color::DARK_GRAY = Color(16, BLK);
const Color Color::RED = Color(199, BLK);
const Color Color::BLUE = Color(39, BLK);
const Color Color::PURPLE = Color(57, BLK);
const Color Color::VIOLET = Color(93, BLK);
const Color Color::INDIGO = Color(21, BLK);
const Color Color::LAVENDER = Color(63, BLK);
const Color Color::GREEN = Color(82, BLK);
const Color Color::YELLOW = Color(226, BLK);
const Color Color::ORANGE = Color(208, BLK);


Color::Color() :
    fg(WHT), bg(BLK)
{
}

Color::Color(short foreground) :
    fg(foreground), bg(BLK)
{
}

Color::Color(short foreground, short background) :
    fg(foreground), bg(background)
{
}

Color::Color(const Color &other) {
    this->fg = other.fg;
    this->bg = other.bg;
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
    this->fg = other.fg;
    this->bg = other.bg;
    return *this;
}

chtype operator | (chtype c, const cursen::Color& n)
{
    if (n.fg == -1 || n.bg == -1) return c;
    return c | CursesManager::GetColorPair(n);
}

chtype operator | (const cursen::Color& n, chtype c)
{
    if (n.fg == -1 || n.bg == -1) return c;
    return c | CursesManager::GetColorPair(n);
}

bool Color::operator==(const Color &other) const {
    return this->bg == other.bg && this->fg == other.fg;
}
