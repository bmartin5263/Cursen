//
// Created by Brandon Martin on 4/15/19.
//

#include <Drawing/CursesManager.h>
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
    cursor_x = 0;
}

void TextField::render() {
    TextComponent::render();
    Content* content = getContent();

    content->clear();
    content->writeLine(text, Size(0,0), TextAlignment::LEFT, getCurrentDrawColor());

    CursesManager::MoveCursor(getPosition() + Size(cursor_x, 0));
}

void TextField::cursorOn() {
    TextComponent::cursorOn();
}

void TextField::keyPress(const Event &e) {
    if (text.size() < max_len) {
        text.insert(text.begin() + cursor_x, (char)e.key.code);
        cursor_x += 1;
        invalidate();
    }
}

void TextField::deletePress(const Event &e) {
    if (!text.empty()) {
        text.erase(text.begin() + (cursor_x-1));
        cursor_x -= 1;
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

void TextField::activate() {
    CursesManager::SetCursor(1);
    CursesManager::MoveCursor(getPosition() + Size((int)text.length(), 0));
    onKeyPress(std::bind(&TextField::keyPress, this, std::placeholders::_1));
    onDeletePress(std::bind(&TextField::deletePress, this, std::placeholders::_1));
    onArrowPress(std::bind(&TextField::moveCursor, this, std::placeholders::_1));
}

void TextField::deactivate() {
    CursesManager::SetCursor(0);
    detachKeyPress();
    detachDeletePress();
    detachArrowPress();
}

TextField::~TextField() {
    deactivate();
}

void TextField::moveCursor(const Event &event) {
    if (event.arrowPress.left && cursor_x > 0) {
        cursor_x -= 1;
        invalidate();
    } else if (event.arrowPress.right && cursor_x < text.size()) {
        cursor_x += 1;
        invalidate();
    }
}
