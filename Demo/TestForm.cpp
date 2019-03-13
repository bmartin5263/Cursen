//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include "Components/Cursor.h"
#include "Components/Label.h"
#include "TestForm.h"

void TestForm::Initialize() {
    c = new Label(Vect2d(1,1), Vect2d(40,1));
    c1 = new Label(Vect2d(1,2), Vect2d(40,1));
    c2 = new Label(Vect2d(1,3), Vect2d(40,1));
    c3 = new Label(Vect2d(1,4), Vect2d(40,1));
    //c->onKeyPress(std::bind(&TestForm::keyPress, this, std::placeholders::_1));
    //c->onEnterPress(std::bind(&TestForm::enterPress, this, std::placeholders::_1));
    //c->onArrowPress(std::bind(&TestForm::arrowPress, this, std::placeholders::_1));
}

void TestForm::Destroy() {
    delete c;
}

void TestForm::keyPress(const Event &event) {
    c->setText("Hello World!");
}

void TestForm::enterPress(const Event &event) {
    c->emplaceText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    c->setText("A very long string");
}


