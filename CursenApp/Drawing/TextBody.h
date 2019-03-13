//
// Created by Brandon Martin on 3/11/19.
//

#ifndef CURSEN_TEXTBODY_H
#define CURSEN_TEXTBODY_H


#include <ncurses.h>
#include <vector>
#include "Vect2d.h"

using namespace cursen;

class TextBody {

public:

    static const char NULL_CHAR = '\0';

    TextBody();
    TextBody(const Vect2d& dimensions);
    ~TextBody();

    void clear();
    void clearLine(const int y);
    void clearColumn(const int x);

    void replaceLine(const chtype *line, const int y);
    void replaceColumn(const chtype *line, const int x);
    void replaceBody(const chtype** const body, const Vect2d &size);

    void writeLine(const char* line, const int y);
    void writeLine(const chtype *line, const int y);
    void writeColumn(const chtype *column, const int x);
    void writeLine(const chtype *line, const Vect2d &loc);
    void writeColumn(const chtype *column, const Vect2d &loc);
    void writeBody(const chtype **const body, const Vect2d &size);
    void writeBody(const chtype **const body, const Vect2d &size, const Vect2d &loc);

    chtype** getContent() { return body; }
    Vect2d getDimensions() { return dimensions; }

    void resize(Vect2d dimensions);

private:

    void assertRange(const int x, const int y);
    void assertX(const int x);
    void assertY(const int y);

    void deleteBody();
    void initializeBody();

    chtype** body;
    Vect2d dimensions;

};


#endif //CURSEN_TEXTBODY_H
