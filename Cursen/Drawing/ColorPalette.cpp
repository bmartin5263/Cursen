//
// Created by Brandon Martin on 3/20/19.
//

#include "ColorPalette.h"

namespace cursen {

    const ColorPalette ColorPalette::DARK = ColorPalette(Color::WHITE, Color::BLACK, Color::YELLOW, Color::GRAY);
    const ColorPalette ColorPalette::LIGHT = ColorPalette(Color::BLACK, Color::WHITE, Color::GRAY, Color::YELLOW);

    ColorPalette::ColorPalette() :
            foreground(Color::WHITE), background(Color::BLACK), highlight(Color::YELLOW), disabled(Color::GRAY)
    {
    }

    ColorPalette::ColorPalette(const Color &foreground, const Color &background, const Color &disabled,
                               const Color &highlight) :
            foreground(foreground), background(background), highlight(highlight), disabled(disabled)
    {
    }


    ColorPalette::ColorPalette(const ColorPalette &other) :
            foreground(other.foreground), background(other.background),
            highlight(other.highlight), disabled(other.disabled) {
    }

    ColorPalette &ColorPalette::operator=(const ColorPalette &other) {
        this->highlight = other.highlight;
        this->disabled = other.disabled;
        this->foreground = other.foreground;
        this->background = other.background;
        return *this;
    }

}