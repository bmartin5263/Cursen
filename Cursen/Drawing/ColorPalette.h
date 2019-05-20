//
// Created by Brandon Martin on 3/20/19.
//

#ifndef CURSEN_COLORPALETTE_H
#define CURSEN_COLORPALETTE_H

#include "Color.h"

namespace cursen {

    class ColorPalette {

    public:

        static const ColorPalette LIGHT;
        static const ColorPalette DARK;

        ColorPalette();
        ColorPalette(const Color& foreground, const Color& background, const Color& disabled, const Color& highlight);
        ColorPalette(const ColorPalette& other);
        ColorPalette& operator = (const ColorPalette& other);
        ~ColorPalette() = default;

        Color getHighlight() { return highlight; }
        Color getForeground() { return foreground; }
        Color getBackground() { return background; }
        Color getDisabled() { return disabled; }

    private:

        Color foreground;
        Color background;
        Color highlight;
        Color disabled;

    };

}


#endif //CURSEN_COLORPALETTE_H
