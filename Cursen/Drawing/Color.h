//
// Created by Brandon Martin on 3/12/19.
//

#ifndef CURSEN_COLOR_H
#define CURSEN_COLOR_H


#include <ncurses.h>
#include <functional>

namespace cursen {

    class Color {

    public:

        static const short BLK;
        static const short WHT;

        static const Color BLACK;
        static const Color WHITE;
        static const Color GRAY;
        static const Color DARK_GRAY;
        static const Color BLUE;
        static const Color DARK_BLUE;
        static const Color PURPLE;
        static const Color VIOLET;
        static const Color INDIGO;
        static const Color LAVENDER;
        static const Color GREEN;
        static const Color YELLOW;
        static const Color MAGENTA;
        static const Color ORANGE;
        static const Color NONE;

        Color();
        Color(short val);
        Color(const Color& other);
        Color& operator = (const Color& other);
        ~Color() = default;

        short getValue();

        static Color RandomColor();

        bool operator==(const Color &other) const;
        bool operator!=(const Color &other) const;

        short val;

    };

    struct color_hash {
        size_t operator()(const Color &name) const
        {
            return std::hash<short>()(name.val);
        }
    };

}

chtype operator | (chtype c, const cursen::Color& n);
chtype operator | (const cursen::Color& n, chtype c);
chtype& operator |= (chtype& c, const cursen::Color& n);
chtype operator ^ (chtype c, const cursen::Color& n);
chtype operator ^ (const cursen::Color& n, chtype c);
chtype& operator ^= (chtype& c, const cursen::Color& n);
//bool operator == (const cursen::Color& lhs, const cursen::Color& rhs);

#endif //CURSEN_COLOR_H
