//
// Created by Brandon on 12/24/21.
//

#include "DemoForm.h"

using namespace cursen;

DemoForm::DemoForm() : Form(Vect2(20, 20)) {}

void DemoForm::initialize() {
    label.initialize();
    label.setPosition(Vect2(0, 1));
    label.setText("Hello, World!");

    button.initialize();
    button.setPosition(Vect2(0, 1));
    button.setLength(10);
    button.setText("Button");

    checkBox.initialize();
    checkBox.setText("Check box");
    checkBox.setState(CheckState::CHECK);

    cursor.initialize();
    cursor.mapComponent(&button, ArrowMap(nullptr, &checkBox, nullptr, &checkBox));
}
