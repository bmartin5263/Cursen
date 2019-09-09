//
// Created by Brandon Martin on 4/15/19.
//

#include <cassert>
#include <Cursen/CursenApplication.h>
#include <Uno/Forms/LobbyForm.h>
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
        Component::setSilenced(true);
        VisualComponent::setHidden(true);

        onKeyPress([&](const Event& event) { this->keyPress(event); });
        onDeletePress([&](const Event& event) { this->deletePress(event); });
        onArrowPress([&](const Event& event) { this->moveCursor(event); });

        text = "";
        stretch = false;
        cursor_x = 0;
        max_len = INT_MAX;
        placeholder_color = ColorPair(Color::GRAY, Color::NONE);

        validate();
    }

    void TextField::render() {
        StandardComponent::render();
        Content& content = getContent();
        ColorPair color = getCurrentDrawColor();

        content.clear();
        int len = getSize().x;

        std::string* text_to_display;
        ColorPair* color_to_display;
        if (text.length() > 0)
        {
            text_to_display = &text;
            color_to_display = &color;
        }
        else
        {
            text_to_display = &placeholder_text;
            color_to_display = &placeholder_color;
        }

        unsigned long padding = len - (*text_to_display).length();

        content.writeLine((*text_to_display), Vect2(0, 0), TextAlignment::LEFT, *color_to_display);
        if (padding > 0) {
            char pad[padding + 1];
            for (int i = 0; i < padding; i++) pad[i] = ' ';
            pad[padding] = '\0';
            content.writeLine(pad, Vect2((int)(*text_to_display).length(), 0), TextAlignment::LEFT, *color_to_display);
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
        if (!text.empty() && cursor_x > 0) {
            text.erase(text.begin() + (cursor_x - 1));
            cursor_x -= 1;
            invalidate();
        }
    }

    void TextField::setMaxLength(int len) {
        max_len = len;
        if (max_len > getSize().x) setSize(Vect2(max_len, 1));
    }

    void TextField::setSize(const Vect2 &size) {
        if (size.y < 1) {
            assert(false);
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

    std::string TextField::getText() const {
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
                setSilenced(false);
                CursesManager::SetCursor(1);
                CursesManager::MoveCursor(getPosition() + Vect2((int) text.length(), 0));
            } else {
                setHidden(true);
                setSilenced(true);
                CursesManager::SetCursor(0);
            }
        }
    }

    void TextField::setPlaceholderText(const std::string& text)
    {
        this->placeholder_text = text;
        invalidate();
    }

    std::string TextField::getPlaceholderText()
    {
        return placeholder_text;
    }

}