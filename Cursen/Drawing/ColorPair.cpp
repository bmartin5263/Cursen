//
// Created by Brandon Martin on 3/19/19.
//

#include <Cursen/CursenApplication.h>
#include "ColorPair.h"
#include "TerminalManager.h"

namespace cursen {

    const ColorPair ColorPair::NONE = ColorPair(Color::NONE, Color::NONE);

    ColorPair::ColorPair() :
            fg(Color::WHITE), bg(Color::BLACK) {
    }

    ColorPair::ColorPair(Color foreground) :
            fg(foreground), bg(Color::BLACK) {
    }

    ColorPair::ColorPair(Color foreground, Color background) :
            fg(foreground), bg(background) {
    }

    ColorPair::ColorPair(const ColorPair &other) {
        this->fg = other.fg;
        this->bg = other.bg;
    }

    ColorPair &ColorPair::operator=(const ColorPair &other) {
        if (this != &other)
        {
            this->fg = other.fg;
            this->bg = other.bg;
        }
        return *this;
    }

    bool ColorPair::operator!=(const ColorPair& other) const
    {
        return !(*this == other);
    }

    bool ColorPair::operator==(const ColorPair &other) const {
        return this->bg == other.bg && this->fg == other.fg;
    }

    short ColorPair::getColorPair() const
    {
        return TerminalManager::GetColorPair(*this);
    }

    bool ColorPair::hasNoneColor() const
    {
        return fg == Color::NONE || bg == Color::NONE;
    }

    void ColorPair::reset()
    {
        if (fg == Color::NONE) fg = CursenApplication::GetColorPalette().getForeground();
        if (bg == Color::NONE) bg = CursenApplication::GetColorPalette().getBackground();
    }

    chtype operator|(chtype c, const ColorPair &n) {
        if (n.hasNoneColor() || c == Content::TRANSPARENT) return c;
        return c | n.getColorPair();
    }

    chtype operator|(const ColorPair &n, chtype c) {
        if (n.hasNoneColor() || c == Content::TRANSPARENT) return c;
        return c | n.getColorPair();
    }

    ColorPair operator|(const Color &c, const ColorPair &n) {
        return ColorPair(n.fg, c);
    }

    ColorPair operator|(const ColorPair &n, const Color &c) {
        return ColorPair(n.fg, c);
    }

    chtype& operator |= (chtype& c, const cursen::ColorPair &n) {
        if (n.fg == Color::NONE || n.bg == Color::NONE || c == Content::TRANSPARENT) return c;
        c |= n.getColorPair();
        return c;
    }
}