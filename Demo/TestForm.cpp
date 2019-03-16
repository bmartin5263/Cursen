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
        c->setColor(Color::PURPLE);
    }
    if (event.key.code == '2') {
        c->setColor(Color(21));
    }
    if (event.key.code == '3') {
        c->setColor(Color(63));
    }
    if (event.key.code == '4') {
        c->setColor(Color(93));
    }
    if (event.key.code == '5') {
        c->setColor(Color::GetRandomColor());
    }
    if (event.key.code == '6') {
        c->setColor(Color::GetRandomColor());
    }
}

void TestForm::enterPress(const Event &event) {
    c->setText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    c->setColor(Color::GRAY);
}



