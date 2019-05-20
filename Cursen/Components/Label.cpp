//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include <Events/AlarmManager.h>
#include "Label.h"

namespace cursen {

    Label::Label() :
            TextComponent(Vect2(0, 0), Vect2(1, 1)) {
    }

    Label::Label(const Vect2 &pos, const Vect2 &dim) :
            TextComponent(pos, dim) {
    }

    void Label::initialize() {
        TextComponent::initialize();
        this->text = "";
        this->alignment = TextAlignment::LEFT;
    }

    void Label::render() {
        TextComponent::render();
        Content *content = getContent();
        ColorPair &draw_color = getCurrentDrawColor();

        content->clear();
        content->writeLine(text, Vect2(0, 0), alignment, draw_color);
    }

    void Label::emplaceText(const std::string &text) {
        this->text = text;
        invalidate();
    }

    void Label::setText(const std::string &text) {
        setSize(Vect2((int) text.length(), 1));
        emplaceText(text);
    }

    void Label::setTextAlignment(const TextAlignment new_alignment) {
        alignment = new_alignment;
        invalidate();
    }

    TextAlignment Label::getTextAlignment() {
        return alignment;
    }

    std::string Label::getText() {
        return text;
    }

}