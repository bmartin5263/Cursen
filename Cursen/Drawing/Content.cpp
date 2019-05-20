//
// Created by Brandon Martin on 3/11/19.
//

#include <cassert>
#include "Content.h"
#include "CursesManager.h"

size_t Content::lineLen(Content::Line const line) {
    size_t i = 0;
    while(line[i] != NULL_CHAR) {
        i++;
    }
    return i;
}

Content::Content() :
    dimensions(Vect2(0,0)), body(nullptr)
{
    resize(dimensions);
}

Content::Content(const Vect2& dimensions) :
    dimensions(dimensions), body(nullptr)
{
    resize(dimensions);
}

void Content::initializeBody() {
    body = new chtype*[dimensions.y + 1];           // +1 for NULL
    for (int i = 0; i < dimensions.y; i++) {
        body[i] = new chtype[dimensions.x + 1];         // +1 for NULL
        for (int j = 0; j < dimensions.x; j++) {
            body[i][j] = ' ';
        }
        body[i][dimensions.x] = NULL_CHAR;
    }
}

void Content::clear() {
    if (!empty) {
        for (int i = 0; i < dimensions.y; i++) {
            for (int j = 0; j < dimensions.x; j++) {
                body[i][j] = ' ';
            }
            body[i][dimensions.x] = NULL_CHAR;
        }
    }
}

void Content::resize(Vect2 dimensions) {
    deleteBody();
    this->dimensions = dimensions;
    empty = dimensions.x <= 0 || dimensions.y <= 0;
    initializeBody();
}

void Content::deleteBody() {
    if (body != nullptr) {
        for (int i = 0; i < dimensions.y; i++) {
            delete[] body[i];
        }
        delete[] body;
        body = nullptr;
    }
}

void Content::clearLine(const int y) {
    if (!empty) {
        assertY(y);
        for (int i = 0; i < dimensions.x; i++) {
            body[y][i] = ' ';
        }
    }
}

void Content::clearColumn(const int x) {
    if (!empty) {
        assertX(x);
        for (int i = 0; i < dimensions.y; i++) {
            body[i][x] = ' ';
        }
    }
}

void Content::writeBody(const Line *const body, const Vect2 &size) {
    writeBody(body, size, Vect2(0,0));
}

void Content::writeBody(const Line *const body, const Vect2 &size, const Vect2 &loc) {
    //int rowIndex = 0;
    //int colIndex = 0;
    //for (int i = loc.y; i < dimensions.y && rowIndex < size.y; i++) {
    //    chtype* row = this->body[i];
    //    for (int j = loc.x; j < dimensions.x && colIndex < size.x; j++) {
    //        row[j] = body[rowIndex][colIndex++];
    //    }
    //    rowIndex++;
    //}

    for (int i = 0; i < size.y; i++) {
        chtype* row = this->body[i];
        for (int j = 0; j < size.x; j++) {
            row[j] = body[i][j];
        }
    }
}

void Content::replaceBody(const Line *const body, const Vect2 &size) {
    clear();
    writeBody(body, size);
}

void Content::replaceLine(Line line, const int y) {
    clearLine(y);
    writeLine(line, Vect2(0, y));
}

void Content::replaceColumn(Line line, const int x) {
    clearColumn(x);
    writeColumn(line, x);
}

void Content::writeLine(const std::string &line, const Vect2 &pos, const TextAlignment &alignment, const ColorPair &color) {
    size_t len = line.length();
    chtype converted[len + 1];
    for (int i = 0; i < len; i++) {
        converted[i] = ((chtype)line[i]) | color;
    }
    converted[len] = NULL_CHAR;
    writeLine(converted, pos, alignment);
}

void Content::writeColumn(const Line column, const int x) {
    writeColumn(column, Vect2(x, 0));
}

void Content::writeLine(const Line line, const Vect2 &loc, const TextAlignment &alignment) {
    if (!empty) {
        assertRange(loc.x, loc.y);
        int index;
        int center;
        int start;
        int end;
        size_t len;
        switch (alignment) {
            case TextAlignment::LEFT:
                index = 0;
                for (int j = loc.x; j < dimensions.x; j++) {
                    if (line[index] == NULL_CHAR) break;
                    body[loc.y][j] = line[index++];
                }
                break;
            case TextAlignment::CENTER:
                len = lineLen(line);
                center = dimensions.x / 2;
                start = center - (int) floor((double) len / 2.0);
                index = 0;
                for (int j = start; j < dimensions.x; j++) {
                    if (line[index] == NULL_CHAR) break;
                    body[loc.y][j] = line[index++];
                }
                break;
            case TextAlignment::RIGHT:
                end = 0;
                while (line[end] != NULL_CHAR) {
                    end++;
                }
                index = dimensions.x - 1;
                for (int j = end; j >= 0; j--) {
                    if (index < 0) break;
                    body[loc.y][index--] = line[j];
                }
                break;
        }
        assert(body[loc.y][dimensions.x] == NULL_CHAR && "Null corrupted");
    }
}

void Content::writeColumn(const Line column, const Vect2 &loc) {
    if (!empty) {
        assertRange(loc.x, loc.y);
        int columnIndex = 0;
        for (int i = loc.y; i < dimensions.y; i++) {
            body[i][loc.x] = column[columnIndex++];
        }
    }
}

void Content::assertRange(const int x, const int y) {
    assertX(x);
    assertY(y);
}

void Content::assertX(const int x) {
    if (x >= dimensions.x) throw std::range_error("X out of range: " + std::to_string(x));
}

void Content::assertY(const int y) {
    if (y >= dimensions.y) throw std::range_error("Y out of range: " + std::to_string(y));
}

Content::~Content() {
    if (body != nullptr) deleteBody();
}

void Content::fillBody(const chtype &c) {
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            body[i][j] = body[i][j] | c;
        }
    }
}

void Content::colorize(const ColorPair &color) {
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            body[i][j] = body[i][j] | color;
        }
    }
}
