//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TEXTBODY_H
#define CURSEN_TEXTBODY_H


#include <ncurses.h>
#include <vector>
#include "Vect2i.h"
#include "Color.h"
#include "TextAlignment.h"

using namespace cursen;

class TextBody {

public:

    typedef chtype* Line;

    static const char NULL_CHAR = '\0';

    TextBody();
    TextBody(const Vect2i& dimensions);
    ~TextBody();

    void clear();
    void clearLine(const int y);
    void clearColumn(const int x);

    void replaceLine(const Line line, const int y);
    void replaceColumn(const Line line, const int x);
    void replaceBody(const Line* const body, const Vect2i &size);

    /**
     * Line writing.
     */
    void writeLine(const std::string &line, const Vect2i &pos,
                   const TextAlignment& alignment = TextAlignment::LEFT, const Color &color = Color::NONE);
    void writeLine(const Line line, const Vect2i &loc, const TextAlignment& alignment = TextAlignment::LEFT);

    void writeColumn(const Line column, const int x);
    void writeColumn(const Line column, const Vect2i &loc);

    void writeBody(const Line *const body, const Vect2i &size);
    void writeBody(const Line *const body, const Vect2i &size, const Vect2i &loc);

    chtype** getContent() { return body; }
    Vect2i getDimensions() { return dimensions; }

    void resize(Vect2i dimensions);

private:

    void assertRange(const int x, const int y);
    void assertX(const int x);
    void assertY(const int y);

    void deleteBody();
    void initializeBody();

    chtype** body;
    Vect2i dimensions;

};


#endif //CURSEN_TEXTBODY_H
