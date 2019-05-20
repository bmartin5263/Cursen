//
// Created by Brandon Martin on 3/21/19.
//

#ifndef CURSEN_CHECKBOX_H
#define CURSEN_CHECKBOX_H

#include "TextComponent.h"
#include "Label.h"
#include "CheckState.h"
#include "AggregateComponent.h"

class CheckBox : public AggregateComponent {

public:

    CheckBox();
    CheckBox(const Vect2 &pos);

    void initialize() override;
    void setText(const std::string& text) override;

    void setState(const CheckState& state);
    void setState(const bool& state);
    void toggle();
    void check();
    void uncheck();

    bool isChecked();

    void cursorOn();
    void cursorOff();

    void setPosition(const Vect2 &size) override;

protected:

    Label box;
    Label text;
    CheckState state;

};


#endif //CURSEN_CHECKBOX_H
