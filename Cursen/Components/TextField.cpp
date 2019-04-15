//
// Created by Brandon Martin on 4/15/19.
//

#include "TextField.h"

TextField::TextField() :
    TextComponent(Size(1,1))
{
}

TextField::TextField(const Size &pos) :
    TextComponent(pos)
{
}

void TextField::initialize() {
    TextComponent::initialize();

    onKeyPress(std::bind(&TextField::keyPress, this, std::placeholders::_1));
    onDeletePress(std::bind(&TextField::deletePress, this, std::placeholders::_1));
}

void TextField::render() {
    TextComponent::render();
    Content* content = getContent();

    content->clear();
    content->writeLine(text, Size(0,0), TextAlignment::LEFT, getCurrentDrawColor());
}

void TextField::cursorOn() {
    TextComponent::cursorOn();
}

void TextField::keyPress(const Event &e) {
    if (text.size() < max_len) {
        text += e.key.code;
        invalidate();
    }
}

void TextField::deletePress(const Event &e) {
    if (!text.empty()) {
        text.pop_back();
        invalidate();
    }
}

void TextField::setMaxLength(const int &len) {
    max_len = len;
}

void TextField::setSize(const Size &size) {
    if (size.y < 1) {
        throw std::range_error("Y Must Be At Least 1");
    }
    TextComponent::setSize(size);
    max_len = size.x;
}

void TextField::setText(const std::string &text) {
    this->text = text;
    invalidate();
}

std::string TextField::getText() {
    return text;
}

TextField::~TextField() {
    detachKeyPress();
    detachDeletePress();
}
