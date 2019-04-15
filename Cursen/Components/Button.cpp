//
// Created by Brandon Martin on 4/5/19.
//

#include "Button.h"

Button::Button() :
    AggregateComponent(Size(0,0)), length(2)
{

}

Button::Button(const Size &pos) :
    AggregateComponent(pos), length(2)
{
}

void Button::setLength(const int& len) {
    if (len < 2) {
        length = 3;
    } else{
        length = len;
    }
    border.setSize(Size(len, 3));
    button_text.setSize(Size(len-2,1));
    invalidate();
}

void Button::initialize() {
    const Size pos = getPosition();

    border.initialize();
    border.setPosition(pos);
    border.setSize(Size(length, 3));
    add(&border);

    button_text.initialize();
    button_text.setPosition(pos + Size(1,1));
    button_text.setSize(Size(length-2, 1));
    button_text.setTextAlignment(TextAlignment::CENTER);
    add(&button_text);

    onCursor(std::bind(&Button::cursorOn, this));
    offCursor(std::bind(&Button::cursorOff, this));

    invalidate();
}

void Button::setText(const std::string &text) {
    button_text.emplaceText(text);
    size_t textLen = text.length();
    if (length < textLen) {
        setLength((int)textLen);
    }
    invalidate();
}

void Button::cursorOn() {
    border.CallOnCursor();
    button_text.CallOnCursor();
}

void Button::cursorOff() {
    border.CallOffCursor();
    button_text.CallOffCursor();
}

void Button::setPosition(const Size &pos) {
    Component::setPosition(pos);
    border.setPosition(pos);
    button_text.setPosition(pos + Size(1,1));
}

//TODO this should be standard in components
void Button::emphasize() {
    border.startGlow();
    button_text.startGlow();
}
