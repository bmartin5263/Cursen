//
// Created by Brandon Martin on 3/12/19.
//

#include "Color.h"
#include "CursesManager.h"

const short Color::BLK = 0;
const short Color::WHT = 15;

const Color Color::BLACK = Color(BLK, BLK);
const Color Color::WHITE = Color(WHT, WHT);
const Color Color::RED = Color(199, BLK);
const Color Color::BLUE = Color(39, BLK);
const Color Color::GREEN = Color(82, BLK);
const Color Color::YELLOW = Color(226, BLK);

Color::Color() :
    fg(WHT), bg(BLK)
{
}

Color::Color(int foreground) :
    fg(foreground), bg(BLK)
{
}

Color::Color(int foreground, int background) :
    fg(foreground), bg(background)
{
}

Color::Color(const Color &other) {
    this->fg = other.fg;
    this->bg = other.bg;
}

Color &Color::operator=(const Color &other) {
    this->fg = other.fg;
    this->bg = other.bg;
    return *this;
}


chtype operator | (chtype c, const cursen::Color& n)
{
    return c | CursesManager::GetColorPair(n);
}


bool Color::operator==(const Color &other) const {
    return this->bg == other.bg && this->fg == other.fg;
}