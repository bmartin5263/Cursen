//
// Created by Brandon Martin on 3/21/19.
//

#ifndef CURSEN_CHECKBOX_H
#define CURSEN_CHECKBOX_H

#include "ColorComponent.h"
#include "Label.h"
#include "CheckState.h"

class CheckBox : public ColorComponent {

public:

    CheckBox();
    CheckBox(const Size &pos);

    void initialize() override;
    void render() override;
    void setText(const std::string& text) override;

    void setState(const CheckState& state);
    void setState(const bool& state);
    void toggle();
    void check();
    void uncheck();

    bool isChecked();

    void cursorOn() override;
    void cursorOff() override;

    void setPosition(const Size &size) override;

protected:

    Label text;
    CheckState state;

};


#endif //CURSEN_CHECKBOX_H
