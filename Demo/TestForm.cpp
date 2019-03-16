//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Components/Cursor.h"
#include "Components/Label.h"
#include "TestForm.h"

void TestForm::initialize() {
    c = new Label(Vect2d(1,1), Vect2d(40,1));
    c->onKeyPress(std::bind(&TestForm::keyPress, this, std::placeholders::_1));
    c->onEnterPress(std::bind(&TestForm::enterPress, this, std::placeholders::_1));
    c->onArrowPress(std::bind(&TestForm::arrowPress, this, std::placeholders::_1));
    addComponent(c);
}

void TestForm::destroy() {
    delete c;
}

void TestForm::keyPress(const Event &event) {
    if (event.key.code == '1') {
        c->setColor(Color::WHITE);
    }
    if (event.key.code == '2') {
        c->setColor(Color::GRAY);
    }
}

void TestForm::enterPress(const Event &event) {
    c->setText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    c->setColor(Color::GRAY);
}



