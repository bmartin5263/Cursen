//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Label.h"

Label::Label(const Vect2i& pos, const Vect2i& dim) :
        Component(pos, dim)
{
    initialize();
}

void Label::initialize() {
    this->color = CursenApplication::GetDefaultColor();
    this->backgroundColor = CursenApplication::GetBackgroundColor();
    this->highlight_color = CursenApplication::GetHighlightColor();
    this->draw_color = ColorPair(this->color, this->backgroundColor);
    this->text = "";
    this->alignment = TextAlignment::LEFT;
    this->onCursor(std::bind(&Label::cursorOn, this));
    this->offCursor(std::bind(&Label::cursorOff, this));
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

void Label::setColor(const Color &color) {
    this->color = color;
    this->draw_color.fg = color;
    invalidate();
}

void Label::changeColor(const Color &color) {
    this->draw_color = color;
    invalidate();
}

void Label::cursorOff() {
    this->draw_color.fg = color;
    this->draw_color.bg = backgroundColor;
    invalidate();
}

void Label::cursorOn() {
    this->draw_color.fg = highlight_color;
    invalidate();
}

void Label::setEnabled(bool value) {
    Component::setEnabled(value);
    if (enabled) {
        changeColor(color);
    }
    else {
        changeColor(Color::GRAY);
    }
}
