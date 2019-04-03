//
// Created by Brandon Martin on 3/21/19.
//

#include <CursenApplication.h>
#include "CheckBox.h"

CheckBox::CheckBox() :
        AggregateComponent()
{
}

CheckBox::CheckBox(const Size &pos) :
        AggregateComponent()
{
        setPosition(pos);
}

void CheckBox::initialize() {
    AggregateComponent::initialize();

    text.initialize();
    text.setPosition(getPosition() + Size(4,0));
    add(&text);

    box.initialize();
    box.setPosition(getPosition());
    add(&box);

    setState(CheckState::UNCHECKED);

    this->onCursor(std::bind(&CheckBox::cursorOn, this));
    this->offCursor(std::bind(&CheckBox::cursorOff, this));
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
            box.setForeground(Color::GREEN);
            box.setText("[X]");
            break;
        case CheckState::UNCHECKED:
            box.setForeground(Color::RED);
            box.setText("[ ]");
            break;
        case CheckState::INDETERMINATE:
            box.setForeground(Color::YELLOW);
            box.setText("[-]");
            break;
    }
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
    text.setPosition(getPosition() + Size(4,0));
    box.setPosition(getPosition());
}
