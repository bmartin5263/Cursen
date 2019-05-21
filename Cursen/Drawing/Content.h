//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TEXTBODY_H
#define CURSEN_TEXTBODY_H


#include <ncurses.h>

#include "Vect2.h"
#include "ColorPair.h"
#include "TextAlignment.h"

namespace cursen {

    class Content {

    public:

        typedef chtype* Line;

        static const char NULL_CHAR = '\0';

        static size_t lineLen(const Line line);

        Content();
        Content(const Vect2& dimensions);
        ~Content();

        void clear();
        void clearLine(const int y);
        void clearColumn(const int x);

        void replaceLine(const Line line, const int y);
        void replaceColumn(const Line line, const int x);
        void replaceBody(const Line* const body, const Vect2 &size);

        /**
         * Line writing.
         */
        void writeLine(const std::string &line, const Vect2 &pos,
                       const TextAlignment& alignment = TextAlignment::LEFT, const ColorPair &color = ColorPair::NONE);
        void writeLine(const Line line, const Vect2 &loc, const TextAlignment& alignment = TextAlignment::LEFT);

        void writeColumn(const Line column, const int x);
        void writeColumn(const Line column, const Vect2 &loc);

        void writeBody(const Line *const body, const Vect2 &size);
        void writeBody(const Line *const body, const Vect2 &size, const Vect2 &loc);
        void fillBody(const chtype& c);

        void colorize(const ColorPair& color);

        chtype** getText() { return body; }
        Vect2 getDimensions() { return dimensions; }

        void resize(Vect2 dimensions);

    private:

        void assertRange(const int x, const int y);
        void assertX(const int x);
        void assertY(const int y);

        void deleteBody();
        void initializeBody();

        chtype** body;
        Vect2 dimensions;
        bool empty;

    };

}

#endif //CURSEN_TEXTBODY_H
