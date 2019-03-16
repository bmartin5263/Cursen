//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Label.h"

Label::Label(const Vect2d& pos, const Vect2d& dim) :
    TextComponent(pos, dim)
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
    this->body.resize(Vect2d(40, 1));
    refresh();
}

void Label::destroy() {

}

void Label::draw() {
    body.writeLine(text, Vect2d(0,0), alignment, draw_color);
}

void Label::emplaceText(const std::string& text) {
    this->text = text;
    refresh();
}

void Label::setText(const std::string& text) {
    body.resize(Vect2d((int)text.length(), 1));
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