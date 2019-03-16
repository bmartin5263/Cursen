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
        static const Color BLUE;
        static const Color GREEN;
        static const Color YELLOW;
        static const Color RED;
        static const Color NONE;

        Color();
        Color(int foreground);
        Color(int foreground, int background);
        Color(const Color& other);
        Color& operator = (const Color& other);
        ~Color() = default;

        static Color GetRandomColor();

        bool operator==(const Color &other) const;

        int fg;
        int bg;

    };

    struct color_hash {
        size_t operator()(const Color &name ) const
        {
            return std::hash<int>()(name.fg) ^ std::hash<int>()(name.bg);
        }
    };

}

chtype operator | (chtype c, const cursen::Color& n);
chtype operator | (const cursen::Color& n, chtype c);
bool operator == (const cursen::Color& lhs, const cursen::Color& rhs);

#endif //CURSEN_COLOR_H
