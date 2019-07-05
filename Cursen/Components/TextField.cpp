//
// Created by Brandon Martin on 4/15/19.
//

#include "Cursen/Drawing/CursesManager.h"
#include "TextField.h"

namespace cursen {

    TextField::TextField() :
            StandardComponent(Vect2(1, 1)) {
    }

    TextField::TextField(const Vect2 &pos) :
            StandardComponent(pos) {
    }

    void TextField::initialize() {
        StandardComponent::initialize();
        Component::setEnabled(false);
        Component::setHidden(true);

        text = "";
        stretch = false;
        cursor_x = 0;
        max_len = INT_MAX;
        active_bg_color = Color::NONE;

        validate();
    }

    void TextField::render() {
        StandardComponent::render();
        Content& content = getContent();

        ColorPair color = getCurrentDrawColor();

        content.clear();

        int len = getSize().x;
        unsigned long padding = len - text.length();
        content.writeLine(text, Vect2(0, 0), TextAlignment::LEFT, color);
        if (padding > 0) {
            if (isEnabled() && active_bg_color != Color::NONE) {
                color.bg = active_bg_color;
            }
            char pad[padding + 1];
            for (int i = 0; i < padding; i++) pad[i] = ' ';
            pad[padding] = '\0';
            content.writeLine(pad, Vect2((int)text.length(), 0), TextAlignment::LEFT, color);
        }

        CursesManager::MoveCursor(getPosition() + Vect2(cursor_x, 0));
    }

    void TextField::cursorOn() {
        StandardComponent::cursorOn();
    }

    void TextField::keyPress(const Event &e) {
        if (text.size() < max_len && e.key.code < 128) {
            text.insert(text.begin() + cursor_x, (char) e.key.code);
            cursor_x += 1;
            invalidate();
        }
    }

    void TextField::deletePress(const Event &e) {
        if (!text.empty()) {
            text.erase(text.begin() + (cursor_x - 1));
            cursor_x -= 1;
            invalidate();
        }
    }

    void TextField::setMaxLength(const int len) {
        max_len = len;
        if (max_len > getSize().x) setSize(Vect2(max_len, 1));
    }

    void TextField::setSize(const Vect2 &size) {
        if (size.y < 1) {
            throw std::range_error("Y Must Be At Least 1");
        }
        StandardComponent::setSize(size);
        max_len = size.x;
    }

    void TextField::setText(const std::string &text) {
        if (text.length() > max_len) {
            setMaxLength((int)text.length());
        }
        this->text = text;
        cursor_x = (int)text.length();
        invalidate();
    }

    std::string TextField::getText() {
        return text;
    }

    TextField::~TextField() {
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

    void TextField::setEnabled(bool value) {
        if (value != isEnabled()) {
            Component::setEnabled(value);
            if (isEnabled()) {
                setHidden(false);
                CursesManager::SetCursor(1);
                CursesManager::MoveCursor(getPosition() + Vect2((int) text.length(), 0));
                onKeyPress(std::bind(&TextField::keyPress, this, std::placeholders::_1));
                onDeletePress(std::bind(&TextField::deletePress, this, std::placeholders::_1));
                onArrowPress(std::bind(&TextField::moveCursor, this, std::placeholders::_1));
            } else {
                setHidden(true);
                CursesManager::SetCursor(0);
                detachKeyPress();
                detachDeletePress();
                detachArrowPress();
            }
        }
    }

    void TextField::setActiveBackgroundColor(Color color)
    {
        active_bg_color = color;
    }

}