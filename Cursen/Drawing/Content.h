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
        static const char TRANSPARENT = 18;

        static size_t lineLen(const Line line);

        Content();
        Content(const Vect2& dimensions);
        ~Content();

        Line& operator [](int);

        void clear();
        void clearLine(int y);
        void clearColumn(int x);

        void replaceLine(const Line line, int y);
        void replaceColumn(const Line line, int x);
        void replaceBody(const Line* const body, const Vect2 &size);

        /**
         * Line writing.
         */
        void writeLine(const std::string &line, const Vect2 &pos,
                       const TextAlignment& alignment = TextAlignment::LEFT, const ColorPair &color = ColorPair::NONE);
        void writeLine(const Line line, const Vect2 &loc, const TextAlignment& alignment = TextAlignment::LEFT);

        void writeColumn(const Line column, int x);
        void writeColumn(const Line column, const Vect2 &loc);

        void writeBody(const Line *const body, const Vect2 &size = Vect2(0,0), const Vect2 &loc = Vect2(0,0));
        void fillBody(const chtype& c);

        void colorize(const ColorPair& color);

        chtype** getText() const { return body; }
        Vect2 getSize() const { return dimensions; }

        void resize(const Vect2& dimensions);

    private:

        inline void assertRange(int x, int y) const;
        inline void assertX(int x) const;
        inline void assertY(int y) const;

        static chtype** CreateBody(chtype** original, const Vect2& original_dim, const Vect2& new_dim);
        static void DeleteBody(chtype**& body, const Vect2& dim);

        void deleteBody();
        void createBody();

        chtype** body;
        Vect2 dimensions;
        bool empty;

    };

}

#endif //CURSEN_TEXTBODY_H
