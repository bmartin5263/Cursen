//
// Created by Brandon Martin on 3/11/19.
//

#include <cassert>
#include "TextBody.h"
#include "CursesManager.h"

TextBody::TextBody() :
    dimensions(Vect2d(0,0)), body(nullptr)
{
    initializeBody();
}

TextBody::TextBody(const Vect2d& dimensions) :
    dimensions(dimensions), body(nullptr)
{
    initializeBody();
}

void TextBody::initializeBody() {
    body = new chtype*[dimensions.y + 1];           // +1 for NULL
    for (int i = 0; i < dimensions.y; i++) {
        body[i] = new chtype[dimensions.x + 1];         // +1 for NULL
        for (int j = 0; j < dimensions.x; j++) {
            body[i][j] = '$';
        }
        body[i][dimensions.x] = NULL_CHAR;
    }
}

void TextBody::clear() {
    for (int i = 0; i < dimensions.y; i++) {
        for (int j = 0; j < dimensions.x; j++) {
            body[i][j] = ' ';
        }
        body[i][dimensions.x] = NULL_CHAR;
    }
}

void TextBody::resize(Vect2d dimensions) {
    deleteBody();
    this->dimensions = dimensions;
    initializeBody();
}

void TextBody::deleteBody() {
    if (body != nullptr) {
        for (int i = 0; i < dimensions.y; i++) {
            delete[] body[i];
        }
        delete[] body;
        body = nullptr;
    }
}

void TextBody::clearLine(const int y) {
    assertY(y);
    for (int i = 0; i < dimensions.x; i++) {
        body[y][i] = ' ';
    }
}

void TextBody::clearColumn(const int x) {
    assertX(x);
    for (int i = 0; i < dimensions.y; i++) {
        body[i][x] = ' ';
    }
}

void TextBody::writeBody(const Line *const body, const Vect2d &size) {
    writeBody(body, size, Vect2d(0,0));
}

void TextBody::writeBody(const Line *const body, const Vect2d &size, const Vect2d &loc) {
    int rowIndex = 0;
    int colIndex = 0;
    for (int i = loc.y; i < dimensions.y && rowIndex < size.y; i++) {
        chtype* row = this->body[i];
        for (int j = loc.x; j < dimensions.x && colIndex < size.x; j++) {
            row[j] = body[rowIndex][colIndex++];
        }
        rowIndex++;
    }
}

void TextBody::replaceBody(const Line *const body, const Vect2d &size) {
    clear();
    writeBody(body, size);
}

void TextBody::replaceLine(Line line, const int y) {
    clearLine(y);
    writeLine(line, Vect2d(0, y));
}

void TextBody::replaceColumn(Line line, const int x) {
    clearColumn(x);
    writeColumn(line, x);
}

void TextBody::writeLine(const std::string &line, const Vect2d &pos, const TextAlignment &alignment, const Color &color) {
    size_t len = line.length();
    chtype converted[len + 1];
    for (int i = 0; i < len; i++) {
        converted[i] = ((chtype)line[i]) | color;
    }
    converted[len] = NULL_CHAR;
    writeLine(converted, pos, alignment);
}

void TextBody::writeColumn(const Line column, const int x) {
    writeColumn(column, Vect2d(x, 0));
}

void TextBody::writeLine(const Line line, const Vect2d &loc, const TextAlignment &alignment) {
    assertRange(loc.x, loc.y);
    int index;
    int i = 0;
    switch (alignment) {
        case TextAlignment::LEFT:
            index = 0;
            for (int i = loc.x; i < dimensions.x; i++) {
                if (line[index] == NULL_CHAR) break;
                body[loc.y][i] = line[index++];
            }
            break;
        case TextAlignment::CENTER:
            break;
        case TextAlignment::RIGHT:
            while (line[i] != NULL_CHAR) {
                i++;
            }
            index = dimensions.x - 1;
            for (int j = i; j >= 0; j--) {
                if (index < 0) break;
                body[loc.y][index--] = line[j];
            }
            break;
    }
    assert(body[loc.y][dimensions.x] == NULL_CHAR && "Null corrupted");
}

void TextBody::writeColumn(const Line column, const Vect2d &loc) {
    assertRange(loc.x, loc.y);
    int columnIndex = 0;
    for (int i = loc.y; i < dimensions.y; i++) {
        body[i][loc.x] = column[columnIndex++];
    }
}

void TextBody::assertRange(const int x, const int y) {
    assertX(x);
    assertY(y);
}

void TextBody::assertX(const int x) {
    if (x < 0 || x >= dimensions.x) throw std::range_error("X out of range: " + std::to_string(x));
}

void TextBody::assertY(const int y) {
    if (y < 0 || y >= dimensions.y) throw std::range_error("Y out of range: " + std::to_string(y));
}

TextBody::~TextBody() {
    if (body != nullptr) deleteBody();
}
