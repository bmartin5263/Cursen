//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TEXTBODY_H
#define CURSEN_TEXTBODY_H


#include <ncurses.h>
#include <vector>
#include "Size.h"
#include "ColorPair.h"
#include "TextAlignment.h"

using namespace cursen;

class Content {

public:

    typedef chtype* Line;

    static const char NULL_CHAR = '\0';

    Content();
    Content(const Size& dimensions);
    ~Content();

    void clear();
    void clearLine(const int y);
    void clearColumn(const int x);

    void replaceLine(const Line line, const int y);
    void replaceColumn(const Line line, const int x);
    void replaceBody(const Line* const body, const Size &size);

    /**
     * Line writing.
     */
    void writeLine(const std::string &line, const Size &pos,
                   const TextAlignment& alignment = TextAlignment::LEFT, const ColorPair &color = ColorPair::NONE);
    void writeLine(const Line line, const Size &loc, const TextAlignment& alignment = TextAlignment::LEFT);

    void writeColumn(const Line column, const int x);
    void writeColumn(const Line column, const Size &loc);

    void writeBody(const Line *const body, const Size &size);
    void writeBody(const Line *const body, const Size &size, const Size &loc);

    chtype** getText() { return body; }
    Size getDimensions() { return dimensions; }

    void resize(Size dimensions);

private:

    void assertRange(const int x, const int y);
    void assertX(const int x);
    void assertY(const int y);

    void deleteBody();
    void initializeBody();

    chtype** body;
    Size dimensions;

};


#endif //CURSEN_TEXTBODY_H
