//
// Created by Brandon Martin on 3/11/19.
//

#include <Drawing/CursesManager.h>
#include <CursenApplication.h>
#include "Cursor/Cursor.h"
#include "Components/Label.h"
#include "TestForm.h"

void TestForm::initialize() {
    box = new Box(Vect2i(1,1), Vect2i(20,8));
    label1 = new Label(Vect2i(2,2), Vect2i(40,1));
    label2 = new Label(Vect2i(2,3), Vect2i(40,1));
    label3 = new Label(Vect2i(2,4), Vect2i(40,1));
    label4 = new Label(Vect2i(2,5), Vect2i(40,1));
    label5 = new Label(Vect2i(10,10), Vect2i(40,1));

    label1->setText("1. Flash");
    label2->setText("2. Beep");
    label3->setText("3. Change Color");
    label4->setText("4. Exit");

    label4->onClick(std::bind(&TestForm::quitGame, this));
    label3->onClick(std::bind(&TestForm::changeColor, this));
    label2->onClick(std::bind(&TestForm::beep, this));
    label1->onClick(std::bind(&TestForm::flash, this));
    box->onArrowPress(std::bind(&TestForm::moveComponent, this, std::placeholders::_1));

    addComponent(label5);
    addComponent(box);
    box->addComponent(label1);
    box->addComponent(label2);
    box->addComponent(label3);
    box->addComponent(label4);

    cursor = new Cursor(label1);
    cursor->addComponent(label1, ArrowMap(nullptr, label4, nullptr, label2));
    cursor->addComponent(label2, ArrowMap(nullptr, label1, nullptr, label3));
    cursor->addComponent(label3, ArrowMap(nullptr, label2, nullptr, label4));
    cursor->addComponent(label4, ArrowMap(nullptr, label3, nullptr, label1));
    cursor->setEnabled(true);
}

void TestForm::keyPress(const Event &event) {
    if (event.key.code == '1') {
        label1->setColor(Color::PURPLE);
    }
    if (event.key.code == '2') {
        label1->setColor(Color(21));
    }
    if (event.key.code == '3') {
        label1->setColor(Color(63));
    }
    if (event.key.code == '4') {
        label1->setColor(Color(93));
    }
    if (event.key.code == '5') {
        label1->setColor(Color::RandomColor());
    }
    if (event.key.code == '6') {
        label1->setColor(Color::RandomColor());
    }
}

void TestForm::enterPress(const Event &event) {
    label1->setText("A very long string");
}

void TestForm::arrowPress(const Event &event) {
    label1->setColor(Color::GRAY);
}

void TestForm::quitGame() {
    CursenApplication::Quit();
}

void TestForm::flash() {
    CursesManager::Flash();
}

void TestForm::beep() {
    CursesManager::Beep();
}

void TestForm::changeColor() {
    box->setColor(Color::RandomColor());
}

void TestForm::moveComponent(const Event &event) {
    if (event.arrowPress.down) {
        box->move(Vect2i(0, 1));
    }
    if (event.arrowPress.up) {
        box->move(Vect2i(0, -1));
    }
    if (event.arrowPress.right) {
        box->move(Vect2i(1, 0));
    }
    if (event.arrowPress.left) {
        box->move(Vect2i(-1, 0));
    }
}



