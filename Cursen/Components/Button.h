//
// Created by Brandon Martin on 4/5/19.
//

#ifndef CURSEN_BUTTON_H
#define CURSEN_BUTTON_H


#include "AggregateComponent.h"
#include "Box.h"
#include "Label.h"

class Button : public AggregateComponent {

public:

    Button();
    Button(const Size &pos);

    void initialize() override;
    void setLength(const int& len);

    void cursorOn();
    void cursorOff();

    void emphasize();

    void setText(const std::string &text) override;
    void setPosition(const Size &pos) override;

private:

    Box border;
    Label button_text;
    int length;

};


#endif //CURSEN_BUTTON_H
