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
    this->color = Color::WHITE;
    this->draw_color = Color::WHITE;
    this->highlight_color = Color::YELLOW;
    this->text = "";
    this->alignment = TextAlignment::LEFT;
    this->onCursor(std::bind(&Label::cursorOn, this));
    this->offCursor(std::bind(&Label::cursorOff, this));
    refresh();
}

void Label::render() {
    body.writeLine(text, Vect2i(0,0), alignment, draw_color);
}

void Label::emplaceText(const std::string& text) {
    this->text = text;
    refresh();
}

void Label::setText(const std::string& text) {
    body.resize(Vect2i((int)text.length(), 1));
    emplaceText(text);
}

void Label::setColor(const Color &color) {
    this->color = color;
    changeColor(this->color);
}

void Label::changeColor(const Color &color) {
    this->draw_color = color;
    refresh();
}

void Label::cursorOff() {
    changeColor(color);
}

void Label::cursorOn() {
    changeColor(highlight_color);
}