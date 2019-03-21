//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Label.h"

Label::Label(const Vect2i& pos, const Vect2i& dim) :
        ColorComponent(pos, dim)
{
    initialize();
}

void Label::initialize() {
    this->text = "";
    this->alignment = TextAlignment::LEFT;
}

void Label::render() {
    content.writeLine(text, Vect2i(0,0), alignment, draw_color);
}

void Label::emplaceText(const std::string& text) {
    this->text = text;
    invalidate();
}

void Label::setText(const std::string& text) {
    content.resize(Vect2i((int)text.length(), 1));
    emplaceText(text);
}