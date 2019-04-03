//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Label.h"

Label::Label() :
        TextComponent(Size(0,0), Size(1,1))
{
}

Label::Label(const Size& pos, const Size& dim) :
        TextComponent(pos, dim)
{
}

void Label::initialize() {
    TextComponent::initialize();
    this->text = "";
    this->alignment = TextAlignment::LEFT;
}

void Label::render() {
    Content* content = getContent();
    ColorPair& draw_color = getCurrentDrawColor();
    content->writeLine(text, Size(0,0), alignment, draw_color);
}

void Label::emplaceText(const std::string& text) {
    this->text = text;
    invalidate();
}

void Label::setText(const std::string& text) {
    setSize(Size((int)text.length(), 1));
    emplaceText(text);
}