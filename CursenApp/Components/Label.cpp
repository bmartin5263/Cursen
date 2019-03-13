//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Label.h"

Label::Label(const Vect2d& pos, const Vect2d& dim) :
    TextComponent(pos, dim)
{
    Initialize();
}

void Label::Initialize() {
    refresh();
}

void Label::Destroy() {

}

void Label::draw() {
    body.writeLine(this->text.c_str(), 0);
}

void Label::setText(const std::string& text) {
    this->text = text;
    refresh();
}

void Label::emplaceText(const std::string& text) {
    body.resize(cursen::Vect2d((int)text.length(), 1));
    setText(text);
}