//
// Created by Brandon Martin on 3/21/19.
//

#include <CursenApplication.h>
#include "CheckBox.h"

CheckBox::CheckBox(const Vect2i &pos) :
        ColorComponent(pos, Vect2i(3,1))
{
    initialize();
}

void CheckBox::initialize() {
    ColorComponent::initialize();
    Vect2i labelPos = position;
    labelPos.x += 4;
    text = new Label(labelPos, Vect2i(1,1));
    setState(CheckState::UNCHECKED);

    add(text);
}

void CheckBox::render() {

    content.clear();

    chtype line[4];
    line[0] = '[' | draw_color;
    switch (state) {
        case CheckState::CHECK:
            line[1] = 'X' | draw_color;
            break;
        case CheckState::UNCHECKED:
            line[1] = ' ' | draw_color;
            break;
        case CheckState::INDETERMINATE:
            line[1] = '-' | draw_color;
            break;
    }
    line[2] = ']' | draw_color;
    line[3] = '\0';


    content.writeLine(line, Vect2i(0,0), TextAlignment::LEFT);

}

void CheckBox::setText(const std::string &text) {
    this->text->setText(text);
}

void CheckBox::cursorOn() {
    this->text->cursorOn();
}

void CheckBox::cursorOff() {
    this->text->cursorOff();
}

void CheckBox::setState(const CheckState &state) {
    this->state = state;
    switch (state) {
        case CheckState::CHECK:
            draw_color = ColorPair(Color::GREEN, background);
            break;
        case CheckState::UNCHECKED:
            draw_color = ColorPair(Color::RED, background);
            break;
        case CheckState::INDETERMINATE:
            draw_color = ColorPair(Color::YELLOW, background);
            break;
    }
    invalidate();
}

void CheckBox::check() {
    setState(CheckState::CHECK);
}

void CheckBox::uncheck() {
    setState(CheckState::UNCHECKED);
}

void CheckBox::switchState() {
    if (state == CheckState::UNCHECKED) {
        check();
    }
    else {
        uncheck();
    }
}

bool CheckBox::isChecked() {
    return state == CheckState::CHECK;
}