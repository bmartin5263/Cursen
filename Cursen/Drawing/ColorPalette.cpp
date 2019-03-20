//
// Created by Brandon Martin on 3/20/19.
//

#include "ColorPalette.h"

ColorPalette::ColorPalette() :
        foreground(Color::WHITE), background(Color::BLACK), disabled(Color::GRAY), highlight(Color::YELLOW)
{
}

ColorPalette::ColorPalette(const Color &foreground, const Color &background, const Color &disabled,
                           const Color &highlight) :
        foreground(foreground), background(background), disabled(disabled), highlight(highlight)
{
}


ColorPalette::ColorPalette(const ColorPalette &other) :
        foreground(other.foreground), background(other.background), disabled(other.disabled), highlight(other.highlight)
{
}

ColorPalette &ColorPalette::operator=(const ColorPalette &other) {
    this->highlight = other.highlight;
    this->disabled = other.disabled;
    this->foreground = other.foreground;
    this->background = other.background;
    return *this;
}
