//
// Created by Brandon Martin on 3/19/19.
//

#ifndef CURSEN_COLORPAIR_H
#define CURSEN_COLORPAIR_H

#include "Color.h"

namespace cursen {

    class ColorPair {

    public:

        static const ColorPair NONE;

        ColorPair();
        ColorPair(Color foreground);
        ColorPair(Color foreground, Color background);
        ColorPair(const ColorPair& other);
        ColorPair& operator = (const ColorPair& other);
        ~ColorPair() = default;

        bool operator==(const ColorPair &other) const;

        Color fg;
        Color bg;

    };

    struct color_pair_hash {
        size_t operator()(const ColorPair &pair ) const
        {
            return std::hash<short>()(pair.fg.val) ^ std::hash<short>()(pair.bg.val);
        }
    };

}

chtype operator | (chtype c, const cursen::ColorPair& n);
chtype operator | (const cursen::ColorPair& n, chtype c);

cursen::ColorPair operator | (const cursen::Color c, const cursen::ColorPair& n);
cursen::ColorPair operator | (const cursen::ColorPair& n, const cursen::Color c);

#endif //CURSEN_COLORPAIR_H
