//
// Created by Brandon Martin on 3/21/19.
//

#include <CursenApplication.h>
#include "CheckBox.h"

CheckBox::CheckBox() :
        ColorComponent(Size(0,0), Size(3,1))
{
}

CheckBox::CheckBox(const Size &pos) :
        ColorComponent(pos, Size(3,1))
{
}

void CheckBox::initialize() {
    ColorComponent::initialize();

    text.initialize();
    Size labelPos = position;
    labelPos.x += 4;
    text.setPosition(labelPos);
    add(&text);

    setState(CheckState::UNCHECKED);
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


    content.writeLine(line, Size(0,0), TextAlignment::LEFT);

}

void CheckBox::setText(const std::string &text) {
    this->text.setText(text);
}

void CheckBox::cursorOn() {
    this->text.cursorOn();
}

void CheckBox::cursorOff() {
    this->text.cursorOff();
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

void CheckBox::setState(const bool &state) {
    if (state) {
        setState(CheckState::CHECK);
    }
    else {
        setState(CheckState::UNCHECKED);
    }
}

void CheckBox::check() {
    setState(CheckState::CHECK);
}

void CheckBox::uncheck() {
    setState(CheckState::UNCHECKED);
}

void CheckBox::toggle() {
    if (state != CheckState::CHECK) {
        check();
    }
    else {
        uncheck();
    }
}

bool CheckBox::isChecked() {
    return state == CheckState::CHECK;
}

void CheckBox::setPosition(const Size &size) {
    Component::setPosition(size);
    Size labelPos = size;
    labelPos.x += 4;
    text.setPosition(labelPos);
}
