//
// Created by Brandon Martin on 3/21/19.
//

#include "CheckBox.h"

namespace cursen {

    CheckBox::CheckBox() :
            AggregateComponent() {
    }

    CheckBox::CheckBox(const Vect2 &pos) :
            AggregateComponent(pos) {
    }

    void CheckBox::initialize() {
        text.initialize();
        text.setPosition(getPosition() + Vect2(4, 0));
        add(text);

        box.initialize();
        box.setPosition(getPosition());
        add(box);

        setState(CheckState::UNCHECKED);

        this->onCursor([&]() { this->cursorOn(); });
        this->offCursor([&]() { this->cursorOff(); });
    }

    void CheckBox::setText(const std::string &text) {
        this->text.setText(text);
    }

    void CheckBox::cursorOn() {
        this->text.CallOnCursor();
    }

    void CheckBox::cursorOff() {
        this->text.CallOffCursor();
    }

    void CheckBox::setState(const CheckState &state) {
        this->state = state;
        switch (state) {
            case CheckState::CHECK:
                box.setForeground(Color::GREEN);
                box.setText("[X]");
                break;
            case CheckState::UNCHECKED:
                box.setForeground(Color::MAGENTA);
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
        } else {
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
        } else {
            uncheck();
        }
    }

    bool CheckBox::isChecked() {
        return state == CheckState::CHECK;
    }

    void CheckBox::setPosition(const Vect2 &size) {
        VisualComponent::setPosition(size);
        text.setPosition(getPosition() + Vect2(4, 0));
        box.setPosition(getPosition());
    }

}