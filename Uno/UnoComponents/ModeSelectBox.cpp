//
// Created by Brandon Martin on 4/10/19.
//

#include "ModeSelectBox.h"

ModeSelectBox::ModeSelectBox() {

}

ModeSelectBox::ModeSelectBox(const Size &pos) : AggregateComponent(pos) {

}

void ModeSelectBox::initialize() {

    border.initialize();
    border.setPosition(Size(0,0));
    border.setSize(Size(36, 21));
    addRelative(&border);

    console_box.initialize();
    console_box.setSize(Size(36, 3));
    console_box.setPosition(Size(0,5));
    console_box.setLowerRight(ACS_RTEE);
    console_box.setLowerLeft(ACS_LTEE);
    console_box.setUpperRight(ACS_RTEE);
    console_box.setUpperLeft(ACS_LTEE);
    addRelative(&console_box);

    console_message.initialize();
    console_message.setPosition(Size(1,6));
    console_message.setForeground(Color::YELLOW);
    console_message.setText("Welcome to Uno! Select a Mode");
    addRelative(&console_message);

}

